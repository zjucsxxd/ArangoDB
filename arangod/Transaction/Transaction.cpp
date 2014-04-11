////////////////////////////////////////////////////////////////////////////////
/// @brief transaction
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2011-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "Transaction.h"

#include "BasicsC/logging.h"
#include "Transaction/Manager.h"

using namespace std;
using namespace triagens::transaction;

#define TRANSACTION_LOG(msg) LOG_INFO("trx #%llu: %s", (unsigned long long) _id, msg)

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief create the transaction
////////////////////////////////////////////////////////////////////////////////

Transaction::Transaction (Manager* manager,
                          IdType id,
                          bool singleOperation,
                          bool waitForSync) 
  : State(),
    _manager(manager),
    _id(id),
    _singleOperation(singleOperation),
    _waitForSync(waitForSync),
    _startTime() {

  TRANSACTION_LOG("creating transaction");
}

////////////////////////////////////////////////////////////////////////////////
/// @brief destroy the transaction
////////////////////////////////////////////////////////////////////////////////

Transaction::~Transaction () {
  if (state() != State::StateType::COMMITTED && 
      state() != State::StateType::ABORTED) {
    this->rollback();
  }

  TRANSACTION_LOG("destroyed transaction");
}

// -----------------------------------------------------------------------------
// --SECTION--                                                    public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief begin a transaction
////////////////////////////////////////////////////////////////////////////////

int Transaction::begin () {
  if (state() != State::StateType::UNINITIALISED) {
    return TRI_ERROR_TRANSACTION_INTERNAL;
  }

  TRANSACTION_LOG("beginning transaction");
  int res = _manager->beginTransaction(this);

  if (res == TRI_ERROR_NO_ERROR) {
    _startTime = TRI_microtime();
  }
  return res;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief commit a transaction
////////////////////////////////////////////////////////////////////////////////
        
int Transaction::commit (bool waitForSync) {
  if (state() != State::StateType::BEGUN) {
    return TRI_ERROR_TRANSACTION_INTERNAL;
  }

  TRANSACTION_LOG("committing transaction");
  return _manager->commitTransaction(this, waitForSync || _waitForSync);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief rollback a transaction
////////////////////////////////////////////////////////////////////////////////
        
int Transaction::rollback () {
  if (state() != State::StateType::BEGUN) {
    return TRI_ERROR_TRANSACTION_INTERNAL;
  }

  TRANSACTION_LOG("rolling back transaction");
  return _manager->rollbackTransaction(this);
}

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
