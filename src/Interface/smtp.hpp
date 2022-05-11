/*
 * Adapted from
 * Copyright (c) 2013 Raivis Strogonovs
 * http://morf.lv
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SMTP_HPP
#define SMTP_HPP

#include <QObject>
#include <QAbstractSocket>

#include <wobjectdefs.h>

class QSslSocket;

namespace Interface {

class smtp : public QObject
{
    W_OBJECT(smtp)

    public:
        explicit smtp(const QString& usr,
                      const QString& pwd,
                      const QString& host,
                      int port = 465,
                      int timeout = 30000);
    ~smtp();

    void sendMail(const QString& from,
                  const QString& to,
                  const QString& subject,
                  const QString& body,
                  const QStringList& files = QStringList());

    void status(const QString& st)
    W_SIGNAL(status, st);

private:
    void stateChanged(QAbstractSocket::SocketState socketState) const
    {
        qDebug() << "stateChanged " << socketState;
    };

    void errorReceived(QAbstractSocket::SocketError socketError) const
    {
        qDebug() << "error " << socketError;
    };

    void disconnected() const;

    void connected() const { qDebug() << "Connected"; };

    void readyRead();

    enum ststes
    {
        Tls,
        HandShake,
        Auth,
        User,
        Pass,
        Rcpt,
        Mail,
        Data,
        Init,
        Body,
        Quit,
        Close
    };

    int state, protocol, timeout, port;
    QTextStream *t;
    QSslSocket* socket;
    QString message,
    from,
    rcpt,
    response,
    usr,
    pwd,
    host;
};

}

#endif // SMTP_HPP
