#ifndef OTHELLO_CLICK_BUTTON_H
#define OTHELLO_CLICK_BUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>

class ClickButton : public QLabel {
    Q_OBJECT

 public:
    explicit ClickButton(QWidget* parent = 0, Qt::WindowFlags flags = 0);

 signals:
    void clicked();

 protected:
    void mousePressEvent(QMouseEvent* event);
};


#endif  // OTHELLO_CLICK_BUTTON_H
