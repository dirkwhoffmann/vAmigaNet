<script lang="ts">
    import { amiga, config, diskController, proxy } from '$lib/stores';
    import { darkTheme, invert } from '$lib/stores';
    import { Opt, Theme, WarpMode } from "$lib/types";

    let wMode: WarpMode = WarpMode.auto; // TODO: Rename to warpMode
    let theme: Theme = Theme.default;
    let canvasBorder = false;
    let shaking = true;

    export function get(option: Opt): string
    {
        console.log("Config.get ", option);

        switch (option) {
            case Opt.WARP_MODE:
                return [wMode].toString();
            case Opt.THEME:
                return [theme].toString();
            case Opt.CANVAS_BORDER:
                return canvasBorder.toString();
            case Opt.SHAKING:
                return shaking.toString();
            default:
                console.warn("get: Invalid option: ", option);
            // TODO: Throw exception
                return "???";
        }
    }

    export function getNum(option: Opt): number
    {
        let result = get(option);
        return result === 'true' ? 1 : result === 'false' ? 0 : Number(result);
    }

    export function getBool(option: Opt): boolean
    {
        let result = get(option);
        return result === 'true' ? true : false;
    }


    export function set(option: Opt, val: string)
    {
        console.log("In set", option, val);
        switch (option) {
            case Opt.WARP_MODE:
                setWarp(val);
                break;
            case Opt.THEME:
                setTheme(val);
                break;
            case Opt.CANVAS_BORDER:
                canvasBorder = val === 'true';
                break;
            case Opt.SHAKING:
                shaking = val === 'true';
                break;
            default:
                console.warn("set: Invalid option: ", option);
            // TODO: Throw exception
        }

        // Force reactive components to update
        $config = $config;
    }

    function setWarp(val: string)
    {
        console.log("setWarp", val);
        wMode = Number(val);
        updateWarpState();
    }

    export function updateWarpState()
    {
        console.log("(updateWarpState", wMode);

        if (!$amiga) return; // GET RID OF THIS

        let newWarp = false;
        switch (wMode) {
            case WarpMode.auto:
                newWarp = $diskController.isSpinning();
                break;
            case WarpMode.never:
                newWarp = false;
                break;
            case WarpMode.always:
                newWarp = true;
                break;
        }

        if (newWarp) {
            $amiga.warpOn();
        } else {
            $amiga.warpOff();
        }
    }

    function setTheme(val: string)
    {
        console.log('setTheme', val);
        theme = val;
        let newTheme = '';
        switch (theme) {
            case Theme.default:
                newTheme = 'mytheme';
                $darkTheme = true;
                $invert = 'invert';
                break;
            case Theme.light:
                newTheme = 'light';
                $darkTheme = true;
                $invert = 'invert';
                break;
            case Theme.dark:
                newTheme = 'dark';
                $darkTheme = true;
                $invert = 'invert';
                break;
            case Theme.coffee:
                newTheme = 'coffee';
                $darkTheme = false;
                $invert = '';
                break;
            case Theme.cupcake:
                newTheme = 'cupcake';
                $darkTheme = false;
                $invert = '';
                break;
            case Theme.forest:
                newTheme = 'forest';
                $darkTheme = true;
                $invert = 'invert';
                break;
            case Theme.aqua:
                newTheme = 'aqua';
                $darkTheme = false;
                $invert = '';
                break;
            case Theme.garden:
                newTheme = 'garden';
                $darkTheme = true;
                $invert = 'invert';
                break;
            case Theme.pastel:
                newTheme = 'pastel';
                $darkTheme = false;
                $invert = '';
                break;
        }

        // Apply new scheme
        document.querySelector('html').setAttribute('data-theme', newTheme);
    }

</script>