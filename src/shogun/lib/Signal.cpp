/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2009 Soeren Sonnenburg
 * Written (W) 2017 Giovanni De Toni
 * Copyright (C) 1999-2009 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include <csignal>
#include <stdlib.h>

#include <shogun/io/SGIO.h>
#include <shogun/lib/Signal.h>
#include <rxcpp/rx-lite.hpp>

using namespace shogun;
using namespace rxcpp;

bool CSignal::m_active = false;
CSignal::SGSubjectS * CSignal::m_subject =
    new rxcpp::subjects::subject<int>();

CSignal::SGObservableS * CSignal::m_observable;
CSignal::SGSubscriberS * CSignal::m_subscriber;

CSignal::CSignal()
{
	// Should prevent memory leak
	if (m_observable != NULL || m_subscriber != NULL)
	{
		delete m_observable;
		delete m_subscriber;
	}
	*(CSignal::m_observable) = m_subject->get_observable();
	*(CSignal::m_subscriber) = m_subject->get_subscriber();
}

CSignal::~CSignal()
{
    delete m_subject;
    delete m_observable;
    delete m_subscriber;
}

void CSignal::handler(int signal)
{
	/* If the handler is not enabled, then return */
	if (!m_active)
		return;

	if (signal == SIGINT)
	{
		SG_SPRINT(
		    "\n[ShogunSignalHandler] "
		    "Immediately return to prompt / "
		    "Prematurely finish computations / "
		    "Pause current computation / "
		    "Do nothing (I/C/P/D)? ")
		char answer = getchar();
		getchar();
		switch (answer)
		{
		case 'I':
			SG_SPRINT("[ShogunSignalHandler] Killing the application...\n");
			m_subscriber->on_completed();
			exit(0);
			break;
		case 'C':
			SG_SPRINT(
			    "[ShogunSignalHandler] Terminating"
			    " prematurely current algorithm...\n");
			m_subscriber->on_next(SG_BLOCK_COMP);
			break;
		case 'P':
			SG_SPRINT("[ShogunSignalHandler] Pausing current computation...")
			m_subscriber->on_next(SG_PAUSE_COMP);
			break;
		default:
			SG_SPRINT("[ShogunSignalHandler] Continuing...\n")
			break;
		}
	}
	else
	{
		SG_SPRINT("[ShogunSignalHandler] Unknown signal %d received\n", signal)
	}
}

void CSignal::reset_handler()
{
    m_subject = new rxcpp::subjects::subject<int>();
    *m_observable = m_subject->get_observable();
    *m_subscriber = m_subject->get_subscriber();
}
