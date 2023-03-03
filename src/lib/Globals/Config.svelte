<script lang="ts">
    import { Opt, RenderMode, Theme, WarpMode } from "$lib/types";
    import { amiga, config, diskController, proxy } from '$lib/stores';
    import { darkTheme, invert } from '$lib/stores';

    // General settings
    let wMode: WarpMode = WarpMode.auto; // TODO: Rename to warpMode
    let theme: Theme = Theme.default;
    let canvasBorder = false;
    let shaking = true;

    // Video settings
    let renderMode = RenderMode.smooth;
    let palette = 0;
    let brightness = 0;
    let contrast = 0;
    let saturation = 0;
    let flickerWeight = 50;

    export function get(option: Opt): string
    {
        switch (option) {
            case Opt.WARP_MODE:
                return [wMode].toString();
            case Opt.THEME:
                return [theme].toString();
            case Opt.CANVAS_BORDER:
                return canvasBorder.toString();
            case Opt.SHAKING:
                return shaking.toString();
            case Opt.RENDER_MODE:
                return renderMode.toString();
            case Opt.PALETTE:
                return $amiga.getConfig($proxy.OPT_PALETTE).toString();
            case Opt.BRIGHTNESS:
                return $amiga.getConfig($proxy.OPT_BRIGHTNESS).toString();
            case Opt.CONTRAST:
                return $amiga.getConfig($proxy.OPT_CONTRAST).toString();
            case Opt.SATURATION:
                return $amiga.getConfig($proxy.OPT_SATURATION).toString();
            case Opt.FLICKER_WEIGHT:
                return flickerWeight.toString();
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
            case Opt.RENDER_MODE:
                renderMode = Number(val);
                break;
            case Opt.PALETTE:
                $amiga.configure($proxy.OPT_PALETTE, Number(val));
                break;
            case Opt.BRIGHTNESS:
                $amiga.configure($proxy.OPT_BRIGHTNESS, Number(val));
                break;
            case Opt.CONTRAST:
                $amiga.configure($proxy.OPT_CONTRAST, Number(val));
                break;
            case Opt.SATURATION:
                $amiga.configure($proxy.OPT_SATURATION, Number(val));
                break;
            case Opt.FLICKER_WEIGHT:
                flickerWeight = Number(flickerWeight);
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