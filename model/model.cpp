#include "model.h"

model::model(QObject *parent) : QObject(parent)
{
    m_tcpserver = new tcpserver;
}

model::~model()
{

}
