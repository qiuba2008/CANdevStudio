#ifndef __CANDEVICE_H
#define __CANDEVICE_H

#include <QScopedPointer>
#include <QtCore/QObject>
#include <componentinterface.h>
#include <context.h>

class CanDevicePrivate;
class QCanBusFrame;

/**
*   @brief The class provides abstraction layer for CAN BUS hardware
*/
class CanDevice : public QObject, public ComponentInterface {
    Q_OBJECT
    Q_DECLARE_PRIVATE(CanDevice)

public:
    CanDevice();
    CanDevice(CanDeviceCtx&& ctx);
    ~CanDevice();

    /**
    *   @brief  Configures CAN BUS backend and interface
    *
    *   This function is used to configure QtCanBus class.
    *
    *   @param  backend one of backends supported by QtCanBus class
    *   @param  iface CAN BUS interface index (e.g. can0 for socketcan backend)
    *   @return true on success, false of failure
    */
    bool init(const QString& backend, const QString& iface);

    /**
    *   @see ComponentInterface
    */
    QWidget* mainWidget() override;

    /**
    *   @see ComponentInterface
    */
    void setConfig(const QJsonObject& json) override;

    /**
    *   @see ComponentInterface
    */
    QJsonObject getConfig() const override;

    /**
    *   @see ComponentInterface
    */
    bool mainWidgetDocked() const override;

signals:
    void frameReceived(const QCanBusFrame& frame);
    void frameSent(bool status, const QCanBusFrame& frame);

    /**
    *   @see ComponentInterface
    */
    void mainWidgetDockToggled(QWidget* widget) override;

public slots:
    void sendFrame(const QCanBusFrame& frame);

    /**
    *   @see ComponentInterface
    */
    void startSimulation() override;

    /**
    *   @see ComponentInterface
    */
    void stopSimulation() override;

private slots:
    void errorOccurred(int error);
    void framesWritten(qint64 framesCnt);
    void framesReceived();

private:
    QScopedPointer<CanDevicePrivate> d_ptr;
};

#endif /* !__CANDEVICE_H */
