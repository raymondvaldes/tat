//
//  integration_boost_units.h
//  tat-test
//
//  Created by Raymond Valdes on 3/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_test_integration_boost_units_h
#define tat_test_integration_boost_units_h

//[ units_define_ode
struct oscillator
{
    frequency_type m_omega;

    oscillator( const frequency_type &omega = 1.0 * si::hertz ) : m_omega( omega ) { }

    void operator()( const state_type &x , deriv_type &dxdt , time_type t ) const
    {
        fusion::at_c< 0 >( dxdt ) = fusion::at_c< 1 >( x );
        fusion::at_c< 1 >( dxdt ) = - m_omega * m_omega * fusion::at_c< 0 >( x );
    }
};
//]


//[ units_observer
struct streaming_observer
{
    std::ostream& m_out;

    streaming_observer( std::ostream &out ) : m_out( out ) { }

    struct write_element
    {
        std::ostream &m_out;
        write_element( std::ostream &out ) : m_out( out ) { };

        template< class T >
        void operator()( const T &t ) const
        {
            m_out << "\t" << t;
        }
    };

    template< class State , class Time >
    void operator()( const State &x , const Time &t ) const
    {
        m_out << t;
        fusion::for_each( x , write_element( m_out ) );
        m_out << "\n";
    }
};
//]

#endif
