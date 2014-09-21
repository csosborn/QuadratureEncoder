QuadratureEncoder
=================

Simple access to rotary and linear motion encoders that use quadrature signalling.

What is it?
-----------

The QuadratureEncoder Arduino library provides an easy way to use motion encoders (like [this one, from Adafruit](http://www.adafruit.com/products/377)) that use two pulsed channels in quadrature to encode direction and distance of motion. Decoding such signals is complicated enough to be well worth keeping separate and abstract, out of your main loop as much as possible.

Each QuadratureEncoder instance uses an internal state machine to decode the quadrature transitions on each of its two input channels, and updates a signed counter to keep track of the motion. For compatibility with the widest possible range of hardware and usage scenarios, it *does not* attempt to configure interrupts, timers, or any other chip facilities for its own use. Instead, it relies on user code to call the `poll()` method periodically, or whenever a transition is observed on either input. For most use cases, it is sufficient to include a call to `poll()` in each iteration of the main Arduino loop. For convenience, this method returns true if an only iff the polling operation resulted in a change in the encoder value. 

### SafetyPin

QuadratureEncoder uses the [SafetyPin](https://github.com/csosborn/SafetyPin) library to provide type-safe specification of digital inputs during construction. Under most circumstances, the DigitalIn input pins should be configured with the optional pull-up resistor enabled.

Classes
-------

### QuadratureEncoder



**Synopsis:**

```Cpp
QuadratureEncoder(const DigitalIn &channelA, const DigitalIn &channelB);   // Constructor

bool poll();             // Update the internal state machine based on the current input values. Returns true if the current value changed as a result of the update.
long read();             // Read the current value.
bool zero();             // Reset the current value to zero.
        
```

