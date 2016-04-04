/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MQTTTEST_H
#define MQTTTEST_H

#include <presentation/Session.h>

#include <mosquittopp.h>

/**
 * Simple mqtt session implementation that connects to a local mqtt server.
 */
class LocalMqtt :
    public Session,
    private mosqpp::mosquittopp
{
public:
  LocalMqtt();
  ~LocalMqtt();

  void send(const std::string &message) override;

  void start();
  void stop();

private:
  const std::string topic{"devices/Device1/messages/devicebound/test"};

};

#endif