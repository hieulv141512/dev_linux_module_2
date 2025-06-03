#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

typedef struct {
    void (*activateAlarm)();
    void (*deactivateAlarm)();
    void (*monitorSensors)();
} SecuritySystem;

SecuritySystem* createSecuritySystem();


#endif  //SECURITY_SYSTEM_H