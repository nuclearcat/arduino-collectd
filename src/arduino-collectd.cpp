#include "arduino-collectd.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
Collectd::Collectd(char *hostname, size_t buffer_size) {
	p = collectd_init_packet(hostname, buffer_size);
	params_set = 0;
}

Collectd::Collectd(char *hostname) {
	p = collectd_init_packet(hostname, 1472);
	params_set = 0;
}

Collectd::~Collectd() {
	if (p)
		collectd_free_packet(p);
}

/* We have several variables required to be set before adding value */
void Collectd::VerifyNecessities(void) {
	if (!(params_set & TIME_SET))
		SetTime(time(NULL));
	if (!(params_set & PLUGIN_SET))
		SetPlugin("default");
	if (!(params_set & TYPE_SET))
		SetType("temperature");
	// These are optional
	//if (!(params_set & PLUGIN_INSTANCE_SET))
	//	SetPluginInstance("default");
	//if (!(params_set & TYPE_INSTANCE_SET))
	//	SetTypeInstance("default");	
}

void Collectd::SetPlugin(char *value) {
  collectd_add_string(p, TYPE_PLUGIN, value);
  params_set |= PLUGIN_SET;
}

void Collectd::SetPluginInstance(char *value) {
  collectd_add_string(p, TYPE_PLUGIN_INSTANCE, value);
  params_set |= PLUGIN_INSTANCE_SET;
}

void Collectd::SetType(char *value) {
	collectd_add_string(p, TYPE_TYPE, value);
	params_set |= TYPE_SET;
}

void Collectd::SetTypeInstance(char *value) {
	collectd_add_string(p, TYPE_TYPE_INSTANCE, value);
	params_set |= TYPE_INSTANCE_SET;
}

void Collectd::SetTime(time_t value) {
	collectd_add_numeric(p, TYPE_TIME, value);
	params_set |= TIME_SET;
}

void Collectd::AddGauge(double value) {
	VerifyNecessities();
	collectd_add_value(p, COLLECTD_VALUETYPE_GAUGE, &value);
	params_set |= VALUE_SET;
}

int Collectd::Send(char *dst_host, int dst_port) {
	WiFiUDP Udp;
	if (!(params_set & VALUE_SET)) {
		// Error, no values set!
		return -1;
	}

	Udp.beginPacket(dst_host, dst_port);
	Udp.write(p->buffer, p->current_offset);
	Udp.endPacket();
	return 0;
}