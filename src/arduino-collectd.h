#ifndef ARDUINO_COLLECTD_H
#define ARDUINO_COLLECTD_H
#include "collectd-embedded/collectd-protocol.h"

#define PLUGIN_SET				(1<<0)
#define PLUGIN_INSTANCE_SET		(1<<1)
#define TYPE_SET				(1<<2)
#define TYPE_INSTANCE_SET		(1<<3)
#define VALUE_SET				(1<<4)
#define TIME_SET				(1<<5)

class Collectd
{
  public:
    Collectd(char *hostname, size_t buffer_size);
    Collectd(char *hostname);
    ~Collectd();
    void SetPlugin(char *);
    void SetPluginInstance(char *);
    void SetType(char *);
    void SetTypeInstance(char *);
	void SetTime(time_t value);
	void VerifyNecessities(void);
    void AddGauge(double value);
    int Send(char *dst_host, int dst_port);
  private:
    struct collectd_packet *p;
    uint8_t params_set;
};

#endif