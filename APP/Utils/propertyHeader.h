#pragma once

#include <qobjectdefs.h>

#define BJ_PROPERTY(type,name) \
Q_PROPERTY(type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
private: type m_##name; \
public: void set_##name(const type& value) {m_##name=value; emit name##Changed(m_##name);} \
        type get_##name(){return m_##name;}
//signals: void name##Changed(const type&);
