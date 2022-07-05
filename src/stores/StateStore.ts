import { State as StateObject } from "$objects/State";
import { writable, type Writable } from "svelte/store";

let _state: StateObject = new StateObject();
export const stateStore: Writable<StateObject> = writable(_state);

export function getState(): StateObject {
    return _state;
}

stateStore.subscribe((newState: StateObject) => {
    _state = newState;
});
