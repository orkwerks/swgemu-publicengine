/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef REFERENCE_H_
#define REFERENCE_H_

#include "../platform.h"

#include "../thread/Atomic.h"

namespace sys {
  namespace lang {

	template<class O> class Reference {
	protected:
		O* _object;
	
		int* _references;
	
	public:
		Reference() {
			_object = NULL;
			_references = NULL;
		}
	
		Reference(Reference<O>& ref) {
			ref.increaseReference();
	
			copyContent(ref);
		}
	
		Reference(O* obj) {
			initializeReference(obj, false);
		}
	
		~Reference() {
			decreaseReference();
		}
	
		void operator=(const Reference<O>& ref) {
			ref.increaseReference();
	
			copyContent(ref);
		}
	
		O* operator->() {
			return _object;
		}
	
	protected:
		inline void initializeReference(O* obj, bool desposable = true) {
			_object = obj;
	
			_references = new int();
			*_references = 1;
		}
	
	private:
		inline void copyContent(const Reference<O>& ref) {
			_object = ref._object;
			_references = ref._references;
		}
	
		inline volatile void increaseReference() {
			Atomic::incrementInt(_references);
		}
	
		inline volatile void decreaseReference() {
			if (!Atomic::decrementInt(_references))
				delete _object;
		}
	
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*REFERENCE_H_*/
