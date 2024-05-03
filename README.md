# Adafruit-NeoPixel-TrinKey-Tool

Set up the Adafruit NeoPixel TrinKey to work as a tiny keyboard for a few specific key commands that it would be a pain to find a full sized keyboard for.

## Purpose

You may be asking yourself, "Why on Earth would you dedicate an entire microcontroller to spamming two keys?"
Great question.
It's because when you are working with old Intel Macs, you cannot use a wireless keyboard to hold down the `Option` key in order to access their boot selector.
It *must* be a wired keyboard. Even the wireless keyboards with a USB receiver do not work.
I had an Adafruit NeoPixel Trinkey on hand, and Adafruit had very easy to follow guides to get me started on using it as an HID device.
I only happen to own one wired keyboard at the moment, and it is connected to my main desktop computer, and *not* portable.
I don't want to have to drag out my custom mechanical keyboard just to access a boot selector screen!


## Where can I get this hardware?

You can find these TrinKeys, and many other variations from [Adafruit here](https://www.adafruit.com/product/4870) for a couple of bucks.
You can also follow along with their [getting started guide](https://learn.adafruit.com/adafruit-neo-trinkey/overview) if you want to work things out for yourself.

## What do it do?

Touch the first pad to hold down the `Option` key (or `KEY_LEFT_ALT` more specifically).
The lights inline with that touch pad will glow orange.
When the pad is no longer being touched, the lights turn off, and the key is no longer sent.

Touch the second pad to hold down `CTRL + ALT + DEL`.
The lights inline with that touchpad will glow blue.
When the pad is no longer being touched, the lights turn off, and the key combo is no longer sent.

> I included `CTRL + ALT + DEL` because it can be used in some server command lines to force a reboot if things are going sideways.
> It can also be used to log out of some Linux Desktops and to bring up the Task Manager on Windows.
> I could not think of anything else to do with this second touch pad, and I felt that htis was a sufficiently useful combo to warrant it taking uo the last spot.
> Feel free to modify this and change it to whatever works best for you.

This is basically just slightly modified example code from Adaafruit, but it was a quick fix to a problem of laziness, so it's a win in my book.
