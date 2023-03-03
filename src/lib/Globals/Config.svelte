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
    /*
    let palette = 0;
    let brightness = 0;
    let contrast = 0;
    let saturation = 0;
    */
    let flickerWeight = 50;

    export function get(option: Opt): string
    {
        switch (option) {

            //
            // General settings
            //

            case Opt.WARP_MODE:
                return [wMode].toString();
            case Opt.THEME:
                return [theme].toString();
            case Opt.CANVAS_BORDER:
                return canvasBorder.toString();
            case Opt.SHAKING:
                return shaking.toString();

            //
            // Machine settings
            //

            case Opt.CPU_REVISION:
                return $amiga.getConfig($proxy.OPT_CPU_REVISION).toString();
            case Opt.CPU_SPEED:
                return $amiga.getConfig($proxy.OPT_CPU_OVERCLOCKING).toString();
            case Opt.AGNUS_REVISION:
                return $amiga.getConfig($proxy.OPT_AGNUS_REVISION).toString();
            case Opt.DENISE_REVISION:
                return $amiga.getConfig($proxy.OPT_DENISE_REVISION).toString();
            case Opt.RTC_MODEL:
                return $amiga.getConfig($proxy.OPT_RTC_MODEL).toString();
            case Opt.CHIP_RAM:
                return $amiga.getConfig($proxy.OPT_CHIP_RAM).toString();
            case Opt.SLOW_RAM:
                return $amiga.getConfig($proxy.OPT_SLOW_RAM).toString();
            case Opt.FAST_RAM:
                return $amiga.getConfig($proxy.OPT_FAST_RAM).toString();
            case Opt.BANK_MAP:
                return $amiga.getConfig($proxy.OPT_BANKMAP).toString();
            case Opt.INIT_PATTERN:
                return $amiga.getConfig($proxy.OPT_RAM_INIT_PATTERN).toString();
            case Opt.UNMAPPED:
                return $amiga.getConfig($proxy.OPT_UNMAPPING_TYPE).toString();
            case Opt.SLOW_RAM_MIRROR:
                return $amiga.getConfig($proxy.OPT_SLOW_RAM_MIRROR).toString();
            case Opt.SLOW_RAM_DELAY:
                return $amiga.getConfig($proxy.OPT_SLOW_RAM_DELAY).toString();
            case Opt.DF0:
                return $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 0).toString();
            case Opt.DF1:
                return $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 1).toString();
            case Opt.DF2:
                return $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 2).toString();
            case Opt.DF3:
                return $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 3).toString();
            case Opt.HD0:
                // TODO
                return 'TODO';

            //
            // Audio settings
            //

            case Opt.AUDVOL0:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 0);
            case Opt.AUDVOL1:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 1);
            case Opt.AUDVOL2:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 2);
            case Opt.AUDVOL3:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 3);
            case Opt.AUDVOLL:
                return $amiga.getConfig($proxy.OPT_AUDVOLL);
            case Opt.AUDVOLR:
                return $amiga.getConfig($proxy.OPT_AUDVOLR);
            case Opt.STEP_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_STEP_VOLUME, 0);
            case Opt.POLL_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_POLL_VOLUME, 0);
            case Opt.INSERT_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_INSERT_VOLUME, 0);
            case Opt.EJECT_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_EJECT_VOLUME, 0);

            //
            // Video settings
            //

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
        return getNum(option) != 0;
    }


    export function set(option: Opt, val: string)
    {
        console.log("In set", option, val);
        switch (option) {

            //
            // General settings
            //

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

            //
            // Machine settings
            //

            case Opt.CPU_REVISION:
                $amiga.configure($proxy.OPT_CPU_REVISION, Number(val));
                break;
            case Opt.CPU_SPEED:
                $amiga.configure($proxy.OPT_CPU_OVERCLOCKING, Number(val));
                break;
            case Opt.AGNUS_REVISION:
                $amiga.configure($proxy.OPT_AGNUS_REVISION, Number(val));
                break;
            case Opt.DENISE_REVISION:
                $amiga.configure($proxy.OPT_DENISE_REVISION, Number(val));
                break;
            case Opt.RTC_MODEL:
                $amiga.configure($proxy.OPT_RTC_MODEL, Number(val));
                break;
            case Opt.CHIP_RAM:
                $amiga.configure($proxy.OPT_CHIP_RAM, Number(val));
                break;
            case Opt.SLOW_RAM:
                $amiga.configure($proxy.OPT_SLOW_RAM, Number(val));
                break;
            case Opt.FAST_RAM:
                $amiga.configure($proxy.OPT_FAST_RAM, Number(val));
                break;
            case Opt.BANK_MAP:
                $amiga.configure($proxy.OPT_BANKMAP, Number(val));
                break;
            case Opt.INIT_PATTERN:
                $amiga.configure($proxy.OPT_RAM_INIT_PATTERN, Number(val));
                break;
            case Opt.UNMAPPED:
                $amiga.configure($proxy.OPT_UNMAPPING_TYPE, Number(val));
                break;
            case Opt.SLOW_RAM_MIRROR:
                $amiga.configure($proxy.OPT_SLOW_RAM_MIRROR, Number(val));
                break;
            case Opt.SLOW_RAM_DELAY:
                $amiga.configure($proxy.OPT_SLOW_RAM_DELAY, Number(val));
                break;
            case Opt.DF0:
                break;
            case Opt.DF1:
                $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 1, val);
                if (val == 0) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 2, 0);
                if (val == 0) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 3, 0);
                break;
            case Opt.DF2:
                if (val == 1) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 1, 1);
                $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 2, val);
                if (val == 0) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 3, 0);
                break;
            case Opt.DF3:
                if (val == 0) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 1, 0);
                if (val == 0) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 2, 0);
                $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 3, val);
                break;
            case Opt.HD0:
                // TODO
                return 'TODO';

            //
            // Audio settings
            //

            case Opt.AUDVOL0:
                $amiga.configureDrive($proxy.OPT_AUDVOL, 0, Number(val));
                break;
            case Opt.AUDVOL1:
                $amiga.configureDrive($proxy.OPT_AUDVOL, 1, Number(val));
                break;
            case Opt.AUDVOL2:
                $amiga.configureDrive($proxy.OPT_AUDVOL, 2, Number(val));
                break;
            case Opt.AUDVOL3:
                $amiga.configureDrive($proxy.OPT_AUDVOL, 3, Number(val));
                break;
            case Opt.AUDVOLL:
                $amiga.configure($proxy.OPT_AUDVOLL, Number(val));
                break;
            case Opt.AUDVOLR:
                $amiga.configure($proxy.OPT_AUDVOLR, Number(val));
                break;
            case Opt.STEP_VOLUME:
                $amiga.configure($proxy.OPT_STEP_VOLUME, Number(val));
                break;
            case Opt.POLL_VOLUME:
                $amiga.configure($proxy.OPT_POLL_VOLUME, Number(val));
                break;
            case Opt.INSERT_VOLUME:
                $amiga.configure($proxy.OPT_INSERT_VOLUME, Number(val));
                break;
            case Opt.EJECT_VOLUME:
                $amiga.configure($proxy.OPT_EJECT_VOLUME, Number(val));
                break;

            //
            // Video settings
            //

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

    function connectDrive(nr: number, connect: boolean)
    {
        if (connect) {
            for (let i = 1; i <= nr; i++) {
                $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, i, 1);
            }
        } else {
            for (let i = nr; i <= 4; i++) {
                $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, i, 0);
            }
        }
    }
</script>