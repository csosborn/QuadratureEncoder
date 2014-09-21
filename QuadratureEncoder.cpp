#include "Arduino.h"
#include "QuadratureEncoder.h"

QuadratureEncoder::QuadratureEncoder(const DigitalIn &channelA, const DigitalIn &channelB) 
	: channelAInput(channelA), channelBInput(channelB), value(0), a(false), b(false) {
		a = channelAInput.read();
		b = channelBInput.read();
}

bool QuadratureEncoder::poll() {
	bool newA = channelAInput.read();
	bool newB = channelBInput.read();
	short delta = 0;
	if (a != newA || b != newB) {
	    switch (state) {
	      case Quiescent:
	        if (!newA && newB) {
	          state = ALeads;
	        } else if (!newB && newA) {
	          state = BLeads;
	        }
	        break;
	      case ALeads:
	        if (!newA && !newB) {
	          state = ALeadsBFollows;
	        }
	        if (newA && newB) {
	          state = Quiescent;
	        }
	        break;
	      case BLeads: 
	        if (!newB && !newA) {
	          state = BLeadsAFollows;
	        } 
	        if (newA && newB) {
	          state = Quiescent;
	        }
	        break;
	      case ALeadsBFollows:
	        if (!newB && newA) {
	          delta = 1;
	          state = ALeadsAReturns;
	        }
	        break;
	      case BLeadsAFollows:
	        if (!newA && newB) {
	          delta = -1;
	          state = BLeadsBReturns;
	        }
	        break;
	      case ALeadsAReturns:
	      case BLeadsBReturns:
	        if (newA && newB) {
	          state = Quiescent;
	        }
	        break;
	    }
	    
	    a = newA;
	    b = newB;

	    value += delta;
	}

	return delta != 0;
}

long QuadratureEncoder::read() const {
	return value;
}

void QuadratureEncoder::zero() {
	value = 0;
}