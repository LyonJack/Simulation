#include "MainViewModel.h"

namespace app
{
    namespace viewModels
    {
        MainViewModel::MainViewModel(QObject* parent) : QObject(parent),
            m_model(NULL)
        {
            m_model = new MainModel();
        }

        MainModel* MainViewModel::model()
        {
            return m_model;
        }

        void MainViewModel::setModel(MainModel* model)
        {
            m_model = model;

            if (m_model)
            {
                connect(this, &MainViewModel::nameChanged, m_model, &MainModel::setName);
                connect(this, &MainViewModel::passwordChanged, m_model, &MainModel::setPassword);
            }
        }

        void MainViewModel::loginButtonClicked()
        {
            if (m_model)
            {
                QString errorCode;
                if (!m_model->login(&errorCode))
                {
                    set_state("Failed:" + errorCode);
                }
                else
                {
                    set_state("Successed");
                }
            }
        }
    }
}
