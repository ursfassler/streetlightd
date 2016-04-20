/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef JSONENCODER_H
#define JSONENCODER_H

#include <protocolstack/application/message/Outgoing.h>
#include <protocolstack/presentation/Message.h>

namespace Json
{

presentation::Message encode(const message::Outgoing &message);

}

#endif
