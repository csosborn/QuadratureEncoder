#ifndef quadrature_encoder_h
#define quadrature_encoder_h

#include <SafetyPin.h>

class QuadratureEncoder {
	private:

		typedef enum EncoderState {
			Quiescent,
			ALeads,
  			ALeadsBFollows,
  			ALeadsAReturns,
  			BLeads,
  			BLeadsAFollows,
  			BLeadsBReturns
		};

		// the current quadrature decoder state machine state
		EncoderState state;
		// the last observed values of the A and B input channels
		bool a, b;

		long value;

		const DigitalIn &channelAInput, &channelBInput;

	public:
		QuadratureEncoder(const DigitalIn &channelA, const DigitalIn &channelB);

		/**
		 * Update the internal state machine based on the current quadrature input values.
		 * Returns true if the update changed the current encoder value (as provided by 
		 * the read() method.
		 */
		bool poll();

		/**
		 * Return the current encoder value.
		 */
		long read() const;

		/**
		 * Zero out the current encoder value.
		 */
		void zero();
};

#endif
