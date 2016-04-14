/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef FORWARDER_H
#define FORWARDER_H

#include "Application.h"

#include <functional>

/**
 * Simple application logic that reads all values on a timeout and forwards it.
 * Same for receiving.
 */
class Forwarder :
    public Application
{
public:
  void timeout() override;
  void received(const message::Incoming &message) override;

  void setBrightnessSensor(Sensor value) override;
  void setLuminosityActor(Actor<double> value) override;
  void setWarningActor(Actor<std::string> value);
  void setSender(Sender value) override;

private:
  Sensor brightnessSensor{};
  Actor<double> luminosityActor{};
  Actor<std::string> warningActor{};
  Sender sender{};

};

#endif
