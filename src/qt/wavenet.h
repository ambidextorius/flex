#ifndef WAVENET_H
#define WAVENET_H

#include <QWidget>
#include <QTimer>
#include <QListWidgetItem>

namespace Ui {
    class WaveNet;
}



class WaveNet : public QWidget
{
    Q_OBJECT

public:
    explicit WaveNet(QWidget *parent = 0);
    ~WaveNet();
    void subscribeToCoreSignals();
    void unsubscribeFromCoreSignals();
    void updateCategories();
    double lastPrice;

public slots:
    void updateCategory(QString category);

private:
    Ui::WaveNet *ui;

private slots:
    void on_tableWidget_itemSelectionChanged();
    void on_categoriesListWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void on_buyButton_clicked();
    void on_viewDetailsButton_clicked();
    void on_copyAddressButton_clicked();
};

#endif // WAVENET_H
