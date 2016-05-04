/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H

#include "../Session.h"
#include "Transfer.h"
#include <infrastructure/SasToken.h>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/URI.h>
#include <memory>
#include <functional>

namespace http
{

class Session final
{
public:
  typedef std::function<void(const std::string &content)> Callback;

  Session(const Poco::URI &uri, const SasTokenFactory &tokenFactory, Callback receiver = [](const std::string &){});

  void get();
  void post(const std::string &content);

private:
  Poco::URI uri;
  const Callback receiver;
  const SasTokenFactory &tokenFactory;
  std::unique_ptr<Poco::Net::HTTPSClientSession> handle{};

  void transfer(const std::string &method, const std::string &content);
  void handleResponseCode(const Transfer &transfer) const;
};

}

#endif
