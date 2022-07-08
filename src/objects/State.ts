export enum DisplayType {
    MOBILE,
    DESKTOP,
}

class URL {
    public root: string = "";
    public documentation: string = `${this.root}/documentation`;
}

class Screen {
    public width: number = -1;
    public height: number = -1;
    public displayType: DisplayType;
}

class Fillcan {
    public version: string = "0.1";
}

export class State {
    constructor() {}

    public URL: URL = new URL();
    public Screen: Screen = new Screen();
    public Fillcan: Fillcan = new Fillcan();
}
