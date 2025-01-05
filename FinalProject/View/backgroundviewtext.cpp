#include "backgroundviewtext.h"
#include "qpixmap.h"
#include <iostream>

void BackgroundViewText::pixmapToString(const QPixmap &pixmap, int xPos, int yPos, int size) {
    QString bgText;

    // Convert the QPixmap to QImage for pixel manipulation
    QImage image = pixmap.toImage();

    // Ensure the image is in a format we can manipulate
    image = image.convertToFormat(QImage::Format_ARGB32);

    int xBegin, yBegin, xEnd, yEnd;
    xBegin = xPos * 4 - size * 4 / 2;
    yBegin = yPos * 4 - size * 4 / 2;
    xEnd = xPos * 4 + size * 4 / 2;
    yEnd = yPos * 4 + size * 4 / 2;
    if (xBegin < 0) {
        xBegin = 0;
        xEnd = size * 4;
    }
    if (yBegin < 0) {
        yBegin = 0;
        yEnd = size * 4;
    }
    if (xEnd > image.width()) {
        xBegin = image.width() - size * 4;
        if (xBegin < 0)
            xBegin = 0;
        xEnd = image.width();
    }
    if (yEnd > image.height()) {
        yBegin = image.height() - size * 4;
        if (yBegin < 0)
            yBegin = 0;
        yEnd = image.height();
    }
    // Loop through each pixel
    bgText.append("<p style=\"line-height:0.5\">");
    for (int y = yBegin; y < image.height() && (y < yEnd); ++y) {
        for (int x = xBegin; x < image.width() && (x < xEnd); ++x) {
            // Get the current pixel color
            QColor color = QColor(image.pixel(x, y));

            bgText.append("<font color=\"");
            bgText.append(color.name());
            bgText.append("\">\u2585</font>");
        }
        bgText.append("<br>");
    }
    bgText.append("</p>");

    emit stringReady(bgText, xPos, yPos);
}


void BackgroundViewText::fastPixmapToString(const QPixmap &pixmap, int xPos, int yPos, int size) {
    QString bgText;

    // Convert the QPixmap to QImage for pixel manipulation
    QImage image = pixmap.toImage();

    // Ensure the image is in a format we can manipulate
    image = image.convertToFormat(QImage::Format_ARGB32);

    int xBegin, yBegin, xEnd, yEnd;
    xBegin = xPos - size / 2;
    yBegin = yPos - size / 2;
    xEnd = xPos + size / 2;
    yEnd = yPos + size / 2;
    if (xBegin < 0) {
        xBegin = 0;
        xEnd = size;
    }
    if (yBegin < 0) {
        yBegin = 0;
        yEnd = size;
    }
    if (xEnd > image.width()) {
        xBegin = image.width() - size;
        if (xBegin < 0)
            xBegin = 0;
        xEnd = image.width();
    }
    if (yEnd > image.height()) {
        yBegin = image.height() - size;
        if (yBegin < 0)
            yBegin = 0;
        yEnd = image.height();
    }
    // Loop through each pixel
    bgText.append("<p style=\"line-height:0.5\">");
    for (int y = yBegin; y < image.height() && (y < yEnd); ++y) {
        for (int x = xBegin; x < image.width() && (x < xEnd); ++x) {
            // Get the current pixel color
            QColor color = QColor(image.pixel(x, y));

            bgText.append("<font color=\"");
            bgText.append(color.name());
            bgText.append("\">\u2585</font>");
        }
        bgText.append("<br>");
    }
    bgText.append("</p>");

    emit stringReady(bgText, xPos, yPos);
}
