#ifndef SINGLE_TIME_FRAME_STRATEGY_H
#define SINGLE_TIME_FRAME_STRATEGY_H

#include "../../indicator/indicator_functions.h"
#include "abstract_strategy.h"
#include "trailing_stop.h"

class QSettings;

class SingleTimeFrameStrategy : public IndicatorFunctions, public AbstractStrategy
{
    Q_OBJECT

protected:
    QList<StandardBar>* barList;
    StandardBar* lastBar;
    _ListProxy<StandardBar> bars;

    TrailingStop trailingStop;
    QSettings *pSettings;

    void setPosition(int newPosition);
    void resetPosition();
    void loadStatus() override;
    void saveStatus() override;
    virtual void checkTPSL(double price);
    virtual void onNewBar() = 0;

public:
    explicit SingleTimeFrameStrategy(const QString &id, const QString &instrumentID, int timeFrame, QObject *parent = nullptr);
    ~SingleTimeFrameStrategy() override;

    //!< Should be called after setParameter
    void setBarList(int timeFrame, QList<StandardBar> *barList, StandardBar *lastBar) override;

    void checkIfNewBar(int newBarTimeFrame) override;
    void onNewTick(qint64 time, double lastPrice) override;

};

#endif // SINGLE_TIME_FRAME_STRATEGY_H
