#ifndef FIXED_ASPECT_RATIO_WIDGET_H
#define OTHELLO_FIXED_ASPECT_RATIO_WIDGET_H


#include <QWidget>


class FixedAspectRationWidget : public QWidget {
 protected:
    void resizeEvent(QResizeEvent * event) {
        if (width() > height()) {
            resize(height(), height());
        } else {
            resize(width(), width());
        }
    }
};

#endif  // OTHELLO_FIXED_ASPECT_RATIO_WIDGET_H
