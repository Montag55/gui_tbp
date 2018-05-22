#ifndef TIMEMANAGER_HPP
#define TIMEMANAGER_HPP

#include <QWidget>
#include <QTimer>

class TimeManager : public QWidget {

    Q_OBJECT

    private:
        QTimer *m_timer = new QTimer(this);
        int m_interval;

    public:
        inline TimeManager(int interval = 1000):
            m_interval{interval}
            {
                this->m_timer->start(interval);
            };

        inline QTimer* get_timer() { return this->m_timer; }

};

#endif // TIMEMANAGER_HPP
