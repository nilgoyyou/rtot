
#ifndef __TRIPLE_BUFFERING_H__
#define __TRIPLE_BUFFERING_H__

#include <boost/thread.hpp>

#include "cv.h"

#include "TimedImage.hpp"
#include "Uncopiable.h"

// Boost Mutex map to a CRITICAL_SECTION on Windows

class TripleBuffering : Uncopiable<> {
	public:
		TripleBuffering(const CvSize s, bool) throw();
		~TripleBuffering(void) throw();
		void write(const IplImage* const frame, DWORD time) throw();
		TimedImage read() throw();
		TimedImage read(int) throw();

	private:
		boost::condition_variable cond_;
		boost::mutex mutswap_;
		boost::mutex mutcond_;
		bool ready_;
        bool blocking_;
		CvSize s_;
		IplImage *buffer1_;
		IplImage *buffer2_;
		IplImage *buffer3_;

        DWORD time1_;
        DWORD time2_;
        DWORD time3_;

		TripleBuffering(const TripleBuffering&);
};

#endif
