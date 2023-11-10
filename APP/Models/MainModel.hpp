#pragma once
#include <qobject.h>

namespace app
{
    namespace modles
    {
        class MainModel : public QObject
        {
            Q_OBJECT
        public:
            explicit MainModel(QObject* parent = 0) {}

            bool login(QString* error) {return true;}

            QString name() { return m_name; }
            void setName(const QString& name) { m_name = name; }

            QString password() { return m_password; }
            void setPassword(const QString& password) { m_password = password; }

        private:
            QString m_name;
            QString m_password;
        };
    }
}
