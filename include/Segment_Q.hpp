#ifndef SEGMENT_Q_HPP
#define SEGMENT_Q_HPP

#include <QWidget>
#include <lib/libtbp/include/base.hpp>
#include <lib/libtbp/include/segment.hpp>


class Segment_Q : public QWidget {

    Q_OBJECT

    public:
        inline Segment_Q(Segment* seg):
            m_seg{seg}
            {};

    private:
        Segment* m_seg;


    public slots:
        inline void set_firstVal(int start){
            m_seg->set_startframe(start);
        }

        inline void set_secondVal(int end){
            m_seg->set_endframe(end);
        }

        inline void set_localIntensity(float inten){
            m_seg->set_local_intensity(inten);
        }

        inline void set_globalIntensity(float inten){
            m_seg->set_global_intensity(inten);
        }
};


#endif // SEGMENT_Q_HPP

