#include "./ClickButton.h"

ClickButton::ClickButton(QWidget* parent, Qt::WindowFlags flags) : QLabel(parent, flags) {}

void ClickButton::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
