export enum DisplayType {
    MOBILE,
    DESKTOP,
}

class URL {
    public root: string = "";
}

class Screen {
    public width: number = -1;
    public height: number = -1;
    public displayType: DisplayType;
}
export class State {
    constructor() {}

    public URL: URL = new URL();
    public Screen: Screen = new Screen();
}
