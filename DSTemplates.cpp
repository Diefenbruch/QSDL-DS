#ifndef _DSTEMPLATES_CC_
#define _DSTEMPLATES_CC_

#ifdef __GNUC__

/* Datei dient der Instantiierung aller Templates */

#include "DSBasicTypes.h"
#include "DSBaseList.h"
#include "DSBaseList.tmpl.h"
#include "DSBaseListElem.h"
#include "DSBaseListElem.tmpl.h"
#include "DSList.h"
#include "DSList.tmpl.h"
#include "DSListElem.h"
#include "DSListElem.tmpl.h"
#include "DSKeyList.h"
#include "DSKeyList.tmpl.h"
#include "DSKeyListElem.tmpl.h"
#include "DSRefList.h"
#include "DSRefList.tmpl.h"
#include "DSRefListElem.h"
#include "DSRefListElem.tmpl.h"
#include "DSStack.h"
#include "DSStack.tmpl.h"

#ifdef USE_PRAGMA
#pragma implementation
#endif

#include "DSAtom.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSAtom>;
template class DSBaseListElem<DSAtom>;
template class DSList<DSAtom>;
template class DSListElem<DSAtom>;

template class DSKeyList<DSAtom, DSString>;
template class DSKeyListElem<DSAtom, DSString>;
#endif

#include "DSAction.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSAction>;
template class DSBaseListElem<DSAction>;
template class DSList<DSAction>;
template class DSListElem<DSAction>;

template class DSBaseList<const DSAction>;
template class DSBaseListElem<const DSAction>;
template class DSRefList<const DSAction>;
template class DSRefListElem<const DSAction>;
#endif

#include "DSBlock.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSBlock>;
template class DSBaseListElem<DSBlock>;
template class DSList<DSBlock>;
template class DSListElem<DSBlock>;

template class DSBaseList<const DSBlock>;
template class DSBaseListElem<const DSBlock>;
template class DSRefList<const DSBlock>;
template class DSRefListElem<const DSBlock>;

template class DSKeyList<DSBlock, DSString>;
template class DSKeyListElem<DSBlock, DSString>;
#endif

#include "DSBlockSubstructure.h"
#ifndef USE_PRAGMA
template class DSBaseList<const DSBlockSubstructure>;
template class DSBaseListElem<const DSBlockSubstructure>;
template class DSRefList<const DSBlockSubstructure>;
template class DSRefListElem<const DSBlockSubstructure>;
#endif

#include "DSCall.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSCall>;
template class DSBaseListElem<DSCall>;
template class DSList<DSCall>;
template class DSListElem<DSCall>;

template class DSBaseList<const DSCall>;
template class DSBaseListElem<const DSCall>;
template class DSRefList<const DSCall>;
template class DSRefListElem<const DSCall>;
#endif

#include "DSChannel.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSChannel>;
template class DSBaseListElem<DSChannel>;
template class DSList<DSChannel>;
template class DSListElem<DSChannel>;

template class DSBaseList<const DSChannel>;
template class DSBaseListElem<const DSChannel>;
template class DSRefList<const DSChannel>;
template class DSRefListElem<const DSChannel>;

template class DSKeyList<DSChannel, DSString>;
template class DSKeyListElem<DSChannel, DSString>;
#endif

#include "DSChannel2RouteConnection.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSChannel2RouteConnection>;
template class DSBaseListElem<DSChannel2RouteConnection>;
template class DSList<DSChannel2RouteConnection>;
template class DSListElem<DSChannel2RouteConnection>;
#endif

#include "DSChannel2ChannelConnection.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSChannel2ChannelConnection>;
template class DSBaseListElem<DSChannel2ChannelConnection>;
template class DSList<DSChannel2ChannelConnection>;
template class DSListElem<DSChannel2ChannelConnection>;
#endif

/*
#include "DSCreate.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSCreate>;
template class DSBaseListElem<DSCreate>;
template class DSList<DSCreate>;
template class DSListElem<DSCreate>;

template class DSBaseList<const DSCreate>;
template class DSBaseListElem<const DSCreate>;
template class DSRefList<const DSCreate>;
template class DSRefListElem<const DSCreate>;
#endif
*/

#include "DSExpression.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSExpression>;
template class DSBaseListElem<DSExpression>;
template class DSList<DSExpression>;
template class DSListElem<DSExpression>;

template class DSBaseList<const DSExpression>;
template class DSBaseListElem<const DSExpression>;
template class DSRefList<const DSExpression>;
template class DSRefListElem<const DSExpression>;
#endif

#include "DSInput.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSInput>;
template class DSBaseListElem<DSInput>;
template class DSList<DSInput>;
template class DSListElem<DSInput>;

template class DSBaseList<const DSInput>;
template class DSBaseListElem<const DSInput>;
template class DSRefList<const DSInput>;
template class DSRefListElem<const DSInput>;
#endif

#include "DSInputSignal.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSInputSignal>;
template class DSBaseListElem<DSInputSignal>;
template class DSList<DSInputSignal>;
template class DSListElem<DSInputSignal>;

template class DSBaseList<const DSInputSignal>;
template class DSBaseListElem<const DSInputSignal>;
template class DSRefList<const DSInputSignal>;
template class DSRefListElem<const DSInputSignal>;
#endif

#include "DSInputTimerSignal.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSInputTimerSignal>;
template class DSBaseListElem<DSInputTimerSignal>;
template class DSList<DSInputTimerSignal>;
template class DSListElem<DSInputTimerSignal>;

template class DSBaseList<const DSInputTimerSignal>;
template class DSBaseListElem<const DSInputTimerSignal>;
template class DSRefList<const DSInputTimerSignal>;
template class DSRefListElem<const DSInputTimerSignal>;
#endif

#include "DSLink.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSLink>;
template class DSBaseListElem<DSLink>;
template class DSList<DSLink>;
template class DSListElem<DSLink>;

template class DSBaseList<const DSLink>;
template class DSBaseListElem<const DSLink>;
template class DSRefList<const DSLink>;
template class DSRefListElem<const DSLink>;

template class DSKeyList<DSLink, DSString>;
template class DSKeyListElem<DSLink, DSString>;
#endif

#include "DSMachine.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSMachine>;
template class DSBaseListElem<DSMachine>;
template class DSList<DSMachine>;
template class DSListElem<DSMachine>;

template class DSBaseList<const DSMachine>;
template class DSBaseListElem<const DSMachine>;
template class DSRefList<const DSMachine>;
template class DSRefListElem<const DSMachine>;

template class DSKeyList<DSMachine, DSString>;
template class DSKeyListElem<DSMachine, DSString>;
#endif

#include "DSMachineService.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSMachineService>;
template class DSBaseListElem<DSMachineService>;
template class DSList<DSMachineService>;
template class DSListElem<DSMachineService>;

template class DSBaseList<const DSMachineService>;
template class DSBaseListElem<const DSMachineService>;
template class DSRefList<const DSMachineService>;
template class DSRefListElem<const DSMachineService>;

template class DSKeyList<DSMachineService, DSString>;
template class DSKeyListElem<DSMachineService, DSString>;
#endif

#include "DSMachineServiceSpeed.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSMachineServiceSpeed>;
template class DSBaseListElem<DSMachineServiceSpeed>;
template class DSList<DSMachineServiceSpeed>;
template class DSListElem<DSMachineServiceSpeed>;
#endif

#include "DSNameSort.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSNameSort>;
template class DSBaseListElem<DSNameSort>;
template class DSList<DSNameSort>;
template class DSListElem<DSNameSort>;

template class DSBaseList<const DSNameSort>;
template class DSBaseListElem<const DSNameSort>;
template class DSRefList<const DSNameSort>;
template class DSRefListElem<const DSNameSort>;

template class DSKeyList<DSNameSort, DSString>;
template class DSKeyListElem<DSNameSort, DSString>;
#endif

#include "DSNextState.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSNextState>;
template class DSBaseListElem<DSNextState>;
template class DSList<DSNextState>;
template class DSListElem<DSNextState>;

template class DSBaseList<const DSNextState>;
template class DSBaseListElem<const DSNextState>;
template class DSRefList<const DSNextState>;
template class DSRefListElem<const DSNextState>;
#endif

#include "DSObject.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSObject>;
template class DSBaseListElem<DSObject>;
template class DSList<DSObject>;
template class DSListElem<DSObject>;

template class DSBaseList<const DSObject>;
template class DSBaseListElem<const DSObject>;
template class DSRefList<const DSObject>;
template class DSRefListElem<const DSObject>;

template class DSRefList<DSObject>;
template class DSRefListElem<DSObject>;

template class DSStack<DSObject>;
template class DSStack<const DSObject>;
#endif

#include "DSOutput.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSOutput>;
template class DSBaseListElem<DSOutput>;
template class DSList<DSOutput>;
template class DSListElem<DSOutput>;

template class DSBaseList<const DSOutput>;
template class DSBaseListElem<const DSOutput>;
template class DSRefList<const DSOutput>;
template class DSRefListElem<const DSOutput>;
#endif

#include "DSPipe.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSPipe>;
template class DSBaseListElem<DSPipe>;
template class DSList<DSPipe>;
template class DSListElem<DSPipe>;

template class DSBaseList<const DSPipe>;
template class DSBaseListElem<const DSPipe>;
template class DSRefList<const DSPipe>;
template class DSRefListElem<const DSPipe>;

template class DSKeyList<DSPipe, DSString>;
template class DSKeyListElem<DSPipe, DSString>;
#endif

#include "DSPipe2LinkBinding.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSPipe2LinkBinding>;
template class DSBaseListElem<DSPipe2LinkBinding>;
template class DSList<DSPipe2LinkBinding>;
template class DSListElem<DSPipe2LinkBinding>;

template class DSBaseList<const DSPipe2LinkBinding>;
template class DSBaseListElem<const DSPipe2LinkBinding>;
template class DSRefList<const DSPipe2LinkBinding>;
template class DSRefListElem<const DSPipe2LinkBinding>;
#endif

#include "DSPipe2PipeBinding.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSPipe2PipeBinding>;
template class DSBaseListElem<DSPipe2PipeBinding>;
template class DSList<DSPipe2PipeBinding>;
template class DSListElem<DSPipe2PipeBinding>;

template class DSBaseList<const DSPipe2PipeBinding>;
template class DSBaseListElem<const DSPipe2PipeBinding>;
template class DSRefList<const DSPipe2PipeBinding>;
template class DSRefListElem<const DSPipe2PipeBinding>;
#endif

#include "DSProcedure.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSProcedure>;
template class DSBaseListElem<DSProcedure>;
template class DSList<DSProcedure>;
template class DSListElem<DSProcedure>;

template class DSBaseList<const DSProcedure>;
template class DSBaseListElem<const DSProcedure>;
template class DSRefList<const DSProcedure>;
template class DSRefListElem<const DSProcedure>;

template class DSKeyList<DSProcedure, DSString>;
template class DSKeyListElem<DSProcedure, DSString>;
#endif

#include "DSProcess.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSProcess>;
template class DSBaseListElem<DSProcess>;
template class DSList<DSProcess>;
template class DSListElem<DSProcess>;

template class DSBaseList<const DSProcess>;
template class DSBaseListElem<const DSProcess>;
template class DSRefList<const DSProcess>;
template class DSRefListElem<const DSProcess>;

template class DSKeyList<DSProcess, DSString>;
template class DSKeyListElem<DSProcess, DSString>;
#endif

#include "DSRange.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSRange>;
template class DSBaseListElem<DSRange>;
template class DSList<DSRange>;
template class DSListElem<DSRange>;
#endif

#include "DSSave.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSave>;
template class DSBaseListElem<DSSave>;
template class DSList<DSSave>;
template class DSListElem<DSSave>;

template class DSBaseList<const DSSave>;
template class DSBaseListElem<const DSSave>;
template class DSRefList<const DSSave>;
template class DSRefListElem<const DSSave>;
#endif

#include "DSSignal.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSignal>;
template class DSBaseListElem<DSSignal>;
template class DSList<DSSignal>;
template class DSListElem<DSSignal>;

template class DSBaseList<const DSSignal>;
template class DSBaseListElem<const DSSignal>;
template class DSRefList<const DSSignal>;
template class DSRefListElem<const DSSignal>;

template class DSKeyList<DSSignal, DSString>;
template class DSKeyListElem<DSSignal, DSString>;
#endif

#include "DSSignalItemList.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSignalItemList>;
template class DSBaseListElem<DSSignalItemList>;
template class DSList<DSSignalItemList>;
template class DSListElem<DSSignalItemList>;

template class DSBaseList<const DSSignalItemList>;
template class DSBaseListElem<const DSSignalItemList>;
template class DSRefList<const DSSignalItemList>;
template class DSRefListElem<const DSSignalItemList>;
#endif

#include "DSSignalslist.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSignalslist>;
template class DSBaseListElem<DSSignalslist>;
template class DSList<DSSignalslist>;
template class DSListElem<DSSignalslist>;

template class DSBaseList<const DSSignalslist>;
template class DSBaseListElem<const DSSignalslist>;
template class DSRefList<const DSSignalslist>;
template class DSRefListElem<const DSSignalslist>;

template class DSKeyList<DSSignalslist, DSString>;
template class DSKeyListElem<DSSignalslist, DSString>;
#endif

#include "DSSignalRoute.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSignalRoute>;
template class DSBaseListElem<DSSignalRoute>;
template class DSList<DSSignalRoute>;
template class DSListElem<DSSignalRoute>;

template class DSBaseList<const DSSignalRoute>;
template class DSBaseListElem<const DSSignalRoute>;
template class DSRefList<const DSSignalRoute>;
template class DSRefListElem<const DSSignalRoute>;

template class DSKeyList<DSSignalRoute, DSString>;
template class DSKeyListElem<DSSignalRoute, DSString>;
#endif

#include "DSOperator.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSOperator>;
template class DSBaseListElem<DSOperator>;
template class DSList<DSOperator>;
template class DSListElem<DSOperator>;

template class DSBaseList<const DSOperator>;
template class DSBaseListElem<const DSOperator>;
template class DSRefList<const DSOperator>;
template class DSRefListElem<const DSOperator>;

template class DSKeyList<DSOperator, DSString>;
template class DSKeyListElem<DSOperator, DSString>;
#endif
/*
#include "DSReset.h"
#ifndef USE_PRAGMA
template class DSList<DSReset>;
template class DSListElem<DSReset>;
template class DSList<const DSReset>;
template class DSListElem<const DSReset>;
template class DSRefList<const DSReset>;
#endif

#include "DSSet.h"
#ifndef USE_PRAGMA
template class DSList<DSSet>;
template class DSListElem<DSSet>;
template class DSList<const DSSet>;
template class DSListElem<const DSSet>;
template class DSRefList<const DSSet>;
#endif
*/

#include "DSSort.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSort>;
template class DSBaseListElem<DSSort>;
template class DSList<DSSort>;
template class DSListElem<DSSort>;

template class DSBaseList<const DSSort>;
template class DSBaseListElem<const DSSort>;
template class DSRefList<const DSSort>;
template class DSRefListElem<const DSSort>;

template class DSKeyList<DSSort, DSString>;
template class DSKeyListElem<DSSort, DSString>;
#endif

#include "DSSortExtended.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSortExtended>;
template class DSBaseListElem<DSSortExtended>;
template class DSList<DSSortExtended>;
template class DSListElem<DSSortExtended>;

template class DSBaseList<const DSSortExtended>;
template class DSBaseListElem<const DSSortExtended>;
template class DSRefList<const DSSortExtended>;
template class DSRefListElem<const DSSortExtended>;

template class DSKeyList<DSSortExtended, DSString>;
template class DSKeyListElem<DSSortExtended, DSString>;
#endif

#include "DSSynonym.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSynonym>;
template class DSBaseListElem<DSSynonym>;
template class DSList<DSSynonym>;
template class DSListElem<DSSynonym>;

template class DSBaseList<const DSSynonym>;
template class DSBaseListElem<const DSSynonym>;
template class DSRefList<const DSSynonym>;
template class DSRefListElem<const DSSynonym>;
#endif

#include "DSState.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSState>;
template class DSBaseListElem<DSState>;
template class DSList<DSState>;
template class DSListElem<DSState>;

template class DSBaseList<const DSState>;
template class DSBaseListElem<const DSState>;
template class DSRefList<const DSState>;
template class DSRefListElem<const DSState>;

template class DSKeyList<DSState, DSString>;
template class DSKeyListElem<DSState, DSString>;
#endif

#include "DSString.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSString>;
template class DSBaseListElem<DSString>;
template class DSList<DSString>;
template class DSListElem<DSString>;

template class DSBaseList<const DSString>;
template class DSBaseListElem<const DSString>;
template class DSRefList<const DSString>;
template class DSRefListElem<const DSString>;

template class DSKeyList<DSString, DSString>;
template class DSKeyListElem<DSString, DSString>;
#endif
/*
#include "DSSystem.h"
#ifndef USE_PRAGMA
template class DSList<DSSystem>;
template class DSListElem<DSSystem>;
template class DSKeyList<DSSystem, DSString>;
template class DSKeyListElem<DSSystem, DSString>;
#endif
*/

#include "DSRequest.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSRequest>;
template class DSBaseListElem<DSRequest>;
template class DSList<DSRequest>;
template class DSListElem<DSRequest>;

template class DSBaseList<const DSRequest>;
template class DSBaseListElem<const DSRequest>;
template class DSRefList<const DSRequest>;
template class DSRefListElem<const DSRequest>;
#endif

/*
#include "DSClear.h"
#ifndef USE_PRAGMA
template class DSList<DSClear>;
template class DSListElem<DSClear>;
template class DSList<const DSClear>;
template class DSListElem<const DSClear>;
template class DSRefList<const DSClear>;
#endif

#include "DSUpdate.h"
#ifndef USE_PRAGMA
template class DSList<DSUpdate>;
template class DSListElem<DSUpdate>;
template class DSList<const DSUpdate>;
template class DSListElem<const DSUpdate>;
template class DSRefList<const DSUpdate>;
#endif

#include "DSTask.h"
#ifndef USE_PRAGMA
template class DSList<DSTask>;
template class DSListElem<DSTask>;
template class DSList<const DSTask>;
template class DSListElem<const DSTask>;
template class DSRefList<const DSTask>;
#endif
*/
#include "DSTimer.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSTimer>;
template class DSBaseListElem<DSTimer>;
template class DSList<DSTimer>;
template class DSListElem<DSTimer>;

template class DSBaseList<const DSTimer>;
template class DSBaseListElem<const DSTimer>;
template class DSRefList<const DSTimer>;
template class DSRefListElem<const DSTimer>;

template class DSKeyList<DSTimer, DSString>;
template class DSKeyListElem<DSTimer, DSString>;
#endif

#include "DSTransition.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSTransition>;
template class DSBaseListElem<DSTransition>;
template class DSList<DSTransition>;
template class DSListElem<DSTransition>;

template class DSBaseList<const DSTransition>;
template class DSBaseListElem<const DSTransition>;
template class DSRefList<const DSTransition>;
template class DSRefListElem<const DSTransition>;
#endif

#include "DSVariable.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSVariable>;
template class DSBaseListElem<DSVariable>;
template class DSList<DSVariable>;
template class DSListElem<DSVariable>;

template class DSBaseList<const DSVariable>;
template class DSBaseListElem<const DSVariable>;
template class DSRefList<const DSVariable>;
template class DSRefListElem<const DSVariable>;

template class DSKeyList<DSVariable, DSString>;
template class DSKeyListElem<DSVariable, DSString>;
#endif

#include "DSVariableAccess.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSVariableAccess>;
template class DSBaseListElem<DSVariableAccess>;
template class DSList<DSVariableAccess>;
template class DSListElem<DSVariableAccess>;

template class DSBaseList<const DSVariableAccess>;
template class DSBaseListElem<const DSVariableAccess>;
template class DSRefList<const DSVariableAccess>;
template class DSRefListElem<const DSVariableAccess>;
#endif

#include "DSVariableAccessElem.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSVariableAccessElem>;
template class DSBaseListElem<DSVariableAccessElem>;
template class DSList<DSVariableAccessElem>;
template class DSListElem<DSVariableAccessElem>;

template class DSBaseList<const DSVariableAccessElem>;
template class DSBaseListElem<const DSVariableAccessElem>;
template class DSRefList<const DSVariableAccessElem>;
template class DSRefListElem<const DSVariableAccessElem>;
#endif

/*
#include "DSVariableAccessField.h"
#ifndef USE_PRAGMA
template class DSList<DSVariableAccessField>;
template class DSListElem<DSVariableAccessField>;
template class DSList<const DSVariableAccessField>;
template class DSListElem<const DSVariableAccessField>;
template class DSRefList<const DSVariableAccessField>;
#endif

#include "DSVariableAccessIndex.h"
#ifndef USE_PRAGMA
template class DSList<DSVariableAccessIndex>;
template class DSListElem<DSVariableAccessIndex>;
template class DSList<const DSVariableAccessIndex>;
template class DSListElem<const DSVariableAccessIndex>;
template class DSRefList<const DSVariableAccessIndex>;
#endif
*/

#include "DSSensor.h"
#ifndef USE_PRAGMA
template class DSBaseList<DSSensor>;
template class DSBaseListElem<DSSensor>;
template class DSList<DSSensor>;
template class DSListElem<DSSensor>;

template class DSBaseList<const DSSensor>;
template class DSBaseListElem<const DSSensor>;
template class DSRefList<const DSSensor>;
template class DSRefListElem<const DSSensor>;

template class DSKeyList<DSSensor, DSString>;
template class DSKeyListElem<DSSensor, DSString>;
#endif

#endif  // __GNUC__

#endif
