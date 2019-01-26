#ifndef _DSREF_H_
#define _DSREF_H_

#include "DSRefList.h"
#include "DSStack.h"

class DSAtom;
typedef const DSAtom *DSAtomRef;

class DSObject;
typedef const DSObject *DSObjectRef;
typedef DSRefList<const DSObject> DSObjectRefList;
typedef DSStack<const DSObject> DSObjectRefStack;
 
class DSExpression;
typedef const DSExpression *DSExpressionRef;
typedef DSRefList<const DSExpression> DSExpressionRefList;

class DSBlock;
typedef const DSBlock *DSBlockRef;
typedef DSRefList<const DSBlock> DSBlockRefList;
 
class DSBlockSubstructure;
typedef const DSBlockSubstructure *DSBlockSubstructureRef;
typedef DSRefList<const DSBlockSubstructure> DSBlockSubstructureRefList;
 
class DSCall;
typedef const DSCall *DSCallRef;
 
class DSChannel;
typedef const DSChannel *DSChannelRef;
typedef DSRefList<const DSChannel> DSChannelRefList;
 
class DSChannel2RouteConnection;
typedef const DSChannel2RouteConnection *DSChannel2RouteConnectionRef;

class DSCreate;
typedef const DSCreate *DSCreateRef;

class DSGenerator;
typedef const DSGenerator *DSGeneratorRef;

class DSInput;
typedef const DSInput *DSInputRef;
typedef DSRefList<const DSInput> DSInputRefList;

class DSSave;
typedef const DSSave *DSSaveRef;
typedef DSRefList<const DSSave> DSSaveRefList;

class DSInputSignal;
typedef const DSInputSignal *DSInputSignalRef;
typedef DSRefList<const DSInputSignal> DSInputSignalRefList;

class DSInputTimerSignal;
typedef const DSInputTimerSignal *DSInputTimerSignalRef;
typedef DSRefList<const DSInputTimerSignal> DSInputTimerSignalRefList;

class DSAction;
typedef const DSAction *DSActionRef;
typedef DSRefList<const DSAction> DSActionRefList;

class DSDecision;
typedef const DSDecision *DSDecisionRef;

class DSNextstate;
typedef const DSNextstate *DSNextstateRef;

class DSCall;
typedef const DSCall *DSCallRef;

class DSCreate;
typedef const DSCreate *DSCreateRef;

class DSState;
typedef const DSState *DSStateRef;
typedef DSRefList<const DSState> DSStateRefList;

class DSNextState;
typedef const DSNextState *DSNextStateRef;
typedef DSRefList<const DSNextState> DSNextStateRefList;

class DSCall;
typedef const DSCall *DSCallRef;
typedef DSRefList<const DSCall> DSCallRefList;

class DSOutput;
typedef const DSOutput *DSOutputRef;
typedef DSRefList<const DSOutput> DSOutputRefList;

class DSReset;
typedef const DSReset *DSResetRef;
typedef DSRefList<const DSReset> DSResetRefList;

class DSSet;
typedef const DSSet *DSSetRef;
typedef DSRefList<const DSSet> DSSetRefList;

class DSTask;
typedef const DSTask *DSTaskRef;
typedef DSRefList<const DSTask> DSTaskRefList;

class DSCreate;
typedef const DSCreate *DSCreateRef;
typedef DSRefList<const DSCreate> DSCreateRefList;

class DSNameSort;
typedef const DSNameSort * DSNameSortRef;
typedef DSRefList<const DSNameSort> DSNameSortRefList;

class DSProcedure;
typedef const DSProcedure *DSProcedureRef;
typedef DSRefList<const DSProcedure> DSProcedureRefList;
 
class DSProcess;
typedef const DSProcess *DSProcessRef;
typedef DSRefList<const DSProcess> DSProcessRefList;
 
class DSRange;
typedef const DSRange *DSRangeRef;
 
class DSSensor;
typedef const DSSensor *DSSensorRef;
typedef DSRefList<const DSSensor> DSSensorRefList;
 
class DSSignal;
typedef const DSSignal *DSSignalRef;
typedef DSRefList<const DSSignal> DSSignalRefList;
 
class DSSignalItemList;
typedef const DSSignalItemList *DSSignalItemListRef;
typedef DSRefList<const DSSignalItemList> DSSignalItemListRefList;
 
class DSSignalslist;
typedef const DSSignalslist *DSSignalslistRef;
typedef DSRefList<const DSSignalslist> DSSignalslistRefList;
 
class DSSignalRoute;
typedef const DSSignalRoute *DSSignalRouteRef;
typedef DSRefList<const DSSignalRoute> DSSignalRouteRefList;
 
class DSOperator;
typedef const DSOperator *DSOperatorRef;
typedef DSRefList<const DSOperator> DSOperatorRefList;
 
class DSSort;
typedef const DSSort *DSSortRef;
typedef DSRefList<const DSSort> DSSortRefList;
 
class DSSortExtended;
typedef const DSSortExtended *DSSortExtendedRef;
typedef DSRefList<const DSSortExtended> DSSortExtendedRefList;
 
class DSState;
typedef const DSState *DSStateRef;
typedef DSRefList<const DSState> DSStateRefList;
 
class DSStruct;
typedef const DSStruct *DSStructRef;
 
class DSSynonym;
typedef const DSSynonym *DSSynonymRef;
typedef DSRefList<const DSSynonym> DSSynonymRefList;
 
class DSSyntype;
typedef const DSSyntype *DSSyntypeRef;
 
class DSSystem;
typedef const DSSystem *DSSystemRef;

class DSTask;
typedef const DSTask *DSTaskRef;
 
class DSTimer;
typedef const DSTimer *DSTimerRef;
typedef DSRefList<const DSTimer> DSTimerRefList;
 
class DSTransition;
typedef const DSTransition *DSTransitionRef;
typedef DSRefList<const DSTransition> DSTransitionRefList;
 
class DSVariable;
typedef const DSVariable *DSVariableRef;
typedef DSRefList<const DSVariable> DSVariableRefList;
  
class DSVariableAccess;
typedef const DSVariableAccess *DSVariableAccessRef;
typedef DSRefList<const DSVariableAccess> DSVariableAccessRefList;
  
class DSString;
typedef const DSString *DSStringRef;
typedef DSRefList<const DSString> DSStringRefList;

class DSMachine;
typedef const DSMachine *DSMachineRef;
typedef DSRefList<const DSMachine> DSMachineRefList;

class DSMachineService;
typedef const DSMachineService *DSMachineServiceRef;
typedef DSRefList<const DSMachineService> DSMachineServiceRefList;

class DSLink;
typedef const DSLink *DSLinkRef;
typedef DSRefList<const DSLink> DSLinkRefList;

class DSPipe;
typedef const DSPipe *DSPipeRef;
typedef DSRefList<const DSPipe> DSPipeRefList;

class DSPipe2LinkBinding;
typedef const DSPipe2LinkBinding *DSPipe2LinkBindingRef;
typedef DSRefList<const DSPipe2LinkBinding> DSPipe2LinkBindingRefList;

class DSRequest;
typedef const DSRequest *DSRequestRef;
typedef DSRefList<const DSRequest> DSRequestRefList;

class DSClear;
typedef const DSClear *DSClearRef;
typedef DSRefList<const DSClear> DSClearRefList;

class DSUpdate;
typedef const DSUpdate *DSUpdateRef;
typedef DSRefList<const DSUpdate> DSUpdateRefList;

#endif
