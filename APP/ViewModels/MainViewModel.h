#pragma once
#include <qobject.h>
#include <QString>
#include "../Models/MainModel.hpp"
#include "../Utils/propertyHeader.h"

using namespace app::modles;

namespace app
{
    namespace viewModels
    {
        class MainViewModel : public QObject
        {
            Q_OBJECT

            BJ_PROPERTY(QString,name)
            BJ_PROPERTY(QString,password)
            BJ_PROPERTY(QString,state)

        public:
            explicit MainViewModel(QObject* parent = 0);

            MainModel* model();
            void setModel(MainModel* model);

            Q_INVOKABLE void loginButtonClicked();

        private:
            MainModel* m_model;
        signals:
            void nameChanged(const QString&);
            void passwordChanged(const QString&);
            void stateChanged(const QString&);
        };
    }
}
