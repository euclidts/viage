/*
 * Adapted from
 * Copyright (c) 2013 Raivis Strogonovs
 * http://morf.lv
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <QFile>
#include <QFileInfo>
#include <QSslSocket>

#include <wobjectimpl.h>

#include "smtp.hpp"

namespace Service {
W_OBJECT_IMPL(smtp)

smtp::smtp(const QString& usr,
           const QString& pwd,
           const QString& host,
           int port,
           int timeout)
    : usr{usr}
    , pwd{pwd}
    , host{host}
    , port{port}
    , timeout{timeout}
    , socket{new QSslSocket(this)}
{
    connect(socket, &QSslSocket::readyRead,
            this, &smtp::readyRead);

    connect(socket, &QSslSocket::connected,
            this, &smtp::connected);

    connect(socket, &QAbstractSocket::errorOccurred,
            this, &smtp::errorReceived);

    connect(socket, &QSslSocket::stateChanged,
            this, &smtp::stateChanged);

    connect(socket, &QSslSocket::disconnected,
            this, &smtp::disconnected);
}

smtp::~smtp()
{
    delete t;
    delete socket;
}

void smtp::sendMail(const QString& from,
                    const QString& to,
                    const QString& subject,
                    const QString& body,
                    const QStringList& files)
{
    bool attachement{!files.isEmpty()};

    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");

    if (attachement)
    {
        // Let's intitiate multipart MIME with cutting boundary "frontier"
        message.append("MIME-Version: 1.0\n");
        message.append("Content-Type: multipart/mixed; boundary=frontier\n\n");

        message.append("--frontier\n");
    }

    // Uncomment this for HTML formating, coment the line below
     message.append("Content-Type: text/html\n\n");
//    message.append("Content-Type: text/plain\n\n");

    message.append(body);
    message.append("\n\n");

    if (attachement)
    {
        qDebug() << "Files to be sent: " << files.size();
        for (const auto& filePath : files)
        {
            QFile file(filePath);
            if (file.exists())
            {
                if (!file.open(QIODevice::ReadOnly))
                {
                    qDebug() << "couldn't open the file";
                    return;
                }

                QByteArray bytes = file.readAll();
                message.append("--frontier\n");
                message.append("Content-Type: application/octet-stream\nContent-Diposition: attachement; filename="+ QFileInfo(file.fileName()).fileName() +";\nContent-Transfer-Encoding: base64\n\n");
                message.append(bytes.toBase64());
                message.append("\n");
            }
        }
    }
    else qDebug() << "No attachements found";

    message.append("--frontier--\n");

    message.replace(QString::fromLatin1("\n"), QString::fromLatin1("\r\n"));
    message.replace(QString::fromLatin1("\r\n.\r\n"),QString::fromLatin1("\r\n..\r\n"));

    this->from = from;
    rcpt = to;
    state = Init;

    socket->connectToHostEncrypted(host, port);
    if (!socket->waitForConnected(timeout))
        qDebug() << socket->errorString();

    t = new QTextStream(socket);
}

void smtp::disconnected() const
{
    qDebug() << "disconnected \n" << "error " << socket->errorString();
}

void smtp::readyRead()
{
    qDebug() << "readyRead";
    // SMTP is line-oriented

    QString responseLine{};

    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    }
    while (socket->canReadLine() && responseLine[3] != ' ');

    responseLine.truncate(3);
    qDebug() << "Server Response code:" << responseLine;
    qDebug() << "Server response: " << response;

    if (state == Init && responseLine == "220")
    {
        // Banner was okay, let's go on
        *t << "EHLO localhost" << "\r\n";
        t->flush();

        state = HandShake;
    }
    else if (state == HandShake && responseLine == "250")
        // This stage currently returns
        // qt.network.ssl: QSslSocket::startClientEncryption: cannot start handshake on non-plain connectionun
        // as described in https://github.com/xcoder123/SimpleSmtp_SSL_QT5/issues/7
        //    {
        //        socket->startClientEncryption();
        //        if (!socket->waitForEncrypted(timeout))
        //        {
        //            qDebug() << socket->errorString();

        //            state = Close;
        ////            return;
        //        }

        //        // Send EHLO once but now encryted
        //        *t << "EHLO localhost" << "\r\n";
        //        t->flush();

        //        state = Auth;
        //    }
        //    else if (state == Auth && responseLine == "250")
    {
        // Trying User
        qDebug() << "Auth";
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();

        state = User;
    }
    else if (state == User && responseLine == "334")
    {
        // Trying User
        qDebug() << "Username";
        *t << usr.toUtf8().toBase64() << "\r\n";
        t->flush();

        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
        //Trying pass
        qDebug() << "Pass";
        *t << pwd.toUtf8().toBase64() << "\r\n";
        t->flush();

        state = Mail;
    }
    else if (state == Mail && responseLine == "235")
    {
        // HELO response was okay (well, it has to be)

        // Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        qDebug() << "MAIL FROM:<" << from << ">";
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();

        state = Rcpt;
    }
    else if (state == Rcpt && responseLine == "250")
    {
        // Apperantly for Google it is mandatory to have MAIL FROM and RCPT email formated the following way -> <email@gmail.com>
        *t << "RCPT TO:<" << rcpt << ">\r\n"; //r
        t->flush();

        state = Data;
    }
    else if (state == Data && responseLine == "250")
    {
        *t << "DATA\r\n";
        t->flush();

        state = Body;
    }
    else if (state == Body && responseLine == "354")
    {
        *t << message << "\r\n.\r\n";
        t->flush();

        state = Quit;
    }
    else if (state == Quit && responseLine == "250")
    {
        *t << "QUIT\r\n";
        t->flush();
        // here, we just close.

        state = Close;
        emit status(tr("Message sent"));
    }
    else if ( state == Close )
    {
        deleteLater();
        return;
    }
    else
    {
        // something broke.
        state = Close;
        emit status(tr("Failed to send message"));
    }

    response = "";
}

}
