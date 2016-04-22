/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryDecoder.h"

#include "Binary.h"

#include <algorithm>

namespace Binary
{

template<typename T>
static T read(std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end);

template<>
double read<double>(std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end)
{
  if (start == end) {
    throw std::invalid_argument("expected 1 byte, got nothing");
  }

  const uint8_t raw = *start;
  start++;

  return double(raw) / 255.0;
}

template<>
std::string read<std::string>(std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end)
{
  if (start == end) {
    throw std::invalid_argument("expected 1 byte, got nothing");
  }

  const uint8_t length = *start;
  start++;

  if (std::distance(start, end) < length) {
    throw std::invalid_argument("invalid length for string: " + std::to_string(length));
  }

  std::string text{};
  const auto textEnd = start + length;
  text.resize(length);
  std::transform(start, textEnd, text.begin(), [](uint8_t sym){return sym;});
  start = textEnd;
  return text;
}

template<typename T>
static void readTo(message::Value<T> &value, std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end)
{
  value = read<T>(start, end);
}

message::Incoming decode(const presentation::Message &message)
{
  const std::vector<uint8_t> data = message.asBinary();

  message::Incoming result{};

  auto start = data.begin();
  auto end = data.end();

  while (start != end) {
    const uint8_t key = *start;
    start++;

    switch (key) {
    case Luminosity: {
      readTo(result.luminosity, start, end);
      break;
    }
    case Warning: {
      readTo(result.warning, start, end);
      break;
    }
    default: {
      throw std::invalid_argument("invalid key: " + std::to_string(key));
      break;
    }
    }
  }

  return result;
}

}