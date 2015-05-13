/**
 * Copyright 2015 Alan Drees
 *
 * Purpose:
 *   Midi Input class definition
 *
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include "RtMidi.h"
#include "input.hpp"
#include "output.hpp"
#include "callback.hpp"

#ifndef MIDI_INPUT_HPP
#define MIDI_INPUT_HPP

typedef void (*msg_callback)(std::vector<unsigned char>*); /**typedef for the message passing callback*/

struct CallbackMessage {
  msg_callback cb; /** callback function */
  int id; /** identifier */
};

class MidiInput: private Input
{
private:
  RtMidiIn *midiin = 0; /** RtMidiIn object reference */
  int midi_instance = 0; /** midi I/O instance to use */
  bool external_midiin = false; /** boolean determining if we need to clean up midiin or not */
  int callback_ids = 0; /** integer counter to keep track of the callback ids */

  std::list<CallbackMessage> message_callbacks; /** std::list of CallbackMessage structures*/

  static void fireMessageEvent(double, std::vector<unsigned char>*, void *);

public:
  MidiInput(int, RtMidiIn*);
  MidiInput(int);
  MidiInput();
  ~MidiInput();

  int addMessageCallback(msg_callback);
  void removeMessageCallback(int);
};
#endif
