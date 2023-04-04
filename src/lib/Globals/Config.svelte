<script lang="ts">
    import { browser } from "$app/environment";
    import { liveQuery } from 'dexie';
    import { Opt, RenderMode, Theme, WarpMode } from "$lib/types";
    import { amiga, config, darkTheme, initialized, invert, proxy } from '$lib/stores';
    import { db, type OptEntry } from '$lib/Db/db';

    //
    // Default settings
    //

    let generalOpts: { opt: Opt, default: string }[] = [
        {opt: Opt.WARP_MODE, default: [WarpMode.auto].toString()},
        {opt: Opt.THEME, default: Theme.default.toString()},
        {opt: Opt.CANVAS_BORDER, default: '0'},
        {opt: Opt.SHAKING, default: '1'}
    ];

    let machineOpts: { opt: Opt, default: string }[] = [
        {opt: Opt.CPU_REVISION, default: '0'},
        {opt: Opt.AGNUS_REVISION, default: '0'},
        {opt: Opt.DENISE_REVISION, default: '0'},
        {opt: Opt.RTC_MODEL, default: '0'},
        {opt: Opt.CHIP_RAM, default: '512'},
        {opt: Opt.SLOW_RAM, default: '512'},
        {opt: Opt.FAST_RAM, default: '0'},
        {opt: Opt.BANK_MAP, default: '0'},
        {opt: Opt.INIT_PATTERN, default: '0'},
        {opt: Opt.UNMAPPED, default: '0'},
        {opt: Opt.SLOW_RAM_MIRROR, default: '1'},
        {opt: Opt.SLOW_RAM_DELAY, default: '1'},
        {opt: Opt.DF0, default: '1'},
        {opt: Opt.DF1, default: '1'},
        {opt: Opt.DF2, default: '0'},
        {opt: Opt.DF3, default: '0'},
        {opt: Opt.HD0, default: '1'},
        {opt: Opt.HD1, default: '0'},
        {opt: Opt.HD2, default: '0'},
        {opt: Opt.HD3, default: '0'}
    ];

    let compatibilityOpts: { opt: Opt, default: string }[] = [
        {opt: Opt.BLITTER_ACCURACY, default: '2'},
        {opt: Opt.TODBUG, default: '1'},
        {opt: Opt.PTR_DROPS, default: '1'},
        {opt: Opt.ECLOCK_SYNCING, default: '1'},
        {opt: Opt.DRIVE_SPEED, default: '1'},
        {opt: Opt.DRIVE_MECHANICS, default: '1'},
        {opt: Opt.OPT_LOCK_DSKSYNC, default: '0'},
        {opt: Opt.OPT_AUTO_DSKSYNC, default: '0'},
        {opt: Opt.CLX_SPR_SPR, default: '0'},
        {opt: Opt.CLX_SPR_PLF, default: '0'},
        {opt: Opt.CLX_PLF_PLF, default: '0'},
        {opt: Opt.ACCURATE_KEYBOARD, default: '1'}
    ];

    let audioOpts: { opt: Opt, default: string }[] = [
        {opt: Opt.AUDVOL0, default: '100'},
        {opt: Opt.AUDVOL1, default: '100'},
        {opt: Opt.AUDVOL2, default: '100'},
        {opt: Opt.AUDVOL3, default: '100'},
        {opt: Opt.AUDVOLL, default: '50'},
        {opt: Opt.AUDVOLR, default: '50'},
        {opt: Opt.STEP_VOLUME, default: '50'},
        {opt: Opt.POLL_VOLUME, default: '50'},
        {opt: Opt.INSERT_VOLUME, default: '50'},
        {opt: Opt.EJECT_VOLUME, default: '50'}
    ];

    let videoOpts: { opt: Opt, default: string }[] = [
        {opt: Opt.RENDER_MODE, default: RenderMode.smooth.toString()},
        {opt: Opt.FLICKER_WEIGHT, default: '0'},
        {opt: Opt.PALETTE, default: '0'},
        {opt: Opt.BRIGHTNESS, default: '50'},
        {opt: Opt.CONTRAST, default: '100'},
        {opt: Opt.SATURATION, default: '50'}
    ];

    // GUI-specific config items that are not stored inside the emulator
    let theme: Theme = Theme.default;
    let canvasBorder = 0;
    let shaking = 1;
    let renderMode = RenderMode.smooth;
    let flickerWeight = 50;

    // Connect to Dexie DB
    let opts: OptEntry[];
    let myQuery = liveQuery(() => (browser ? db.opts.toArray() : []));
    myQuery.subscribe(value => {
        opts = value as OptEntry[]
    })

    // $: console.log("CONFIG DB: ", opts);

    $: if ($initialized) {
        registerDefaults();
        loadSettings();
    }

    //
    // Registering default settings
    //

    async function registerDefaults()
    {
        await registerGeneralDefaults();
        await registerMachineDefaults();
        await registerCompatibilityDefaults();
        await registerAudioDefaults();
        await registerVideoDefaults();
    }

    async function registerGeneralDefaults()
    {
        for (const it of generalOpts) {
            await registerDefault(it.opt, it.default);
        }
    }

    async function registerMachineDefaults()
    {
        for (const it of machineOpts) {
            await registerDefault(it.opt, it.default);
        }
    }

    async function registerCompatibilityDefaults()
    {
        for (const it of compatibilityOpts) {
            await registerDefault(it.opt, it.default);
        }
    }

    async function registerAudioDefaults()
    {
        for (const it of audioOpts) {
            await registerDefault(it.opt, it.default);
        }
    }

    async function registerVideoDefaults()
    {
        for (const it of videoOpts) {
            await registerDefault(it.opt, it.default);
        }
    }

    async function registerDefault(opt: Opt, value: string)
    {
        try {
            await db.opts.add({key: opt, value: value});
        } catch (error) {
            // The item is registered already
        }
    }

    //
    // Restoring default settings
    //

    export async function restoreDefaults()
    {
        await restoreGeneralDefaults();
        await restoreMachineDefaults();
        await restoreCompatibilityDefaults();
        await restoreAudioDefaults();
        await restoreVideoDefaults();
    }

    export async function restoreGeneralDefaults()
    {
        for (const it of generalOpts) {
            await deleteDefault(it.opt);
        }

        await registerGeneralDefaults();
        await loadGeneralSettings();
    }

    export async function restoreMachineDefaults()
    {
        for (const it of machineOpts) {
            await deleteDefault(it.opt);
        }

        await registerMachineDefaults();
        await loadMachineSettings();
    }

    export async function restoreCompatibilityDefaults()
    {
        for (const it of compatibilityOpts) {
            await deleteDefault(it.opt);
        }

        await registerCompatibilityDefaults();
        await loadCompatibilitySettings();
    }

    export async function restoreAudioDefaults()
    {
        for (const it of audioOpts) {
            await deleteDefault(it.opt);
        }

        await registerAudioDefaults();
        await loadAudioSettings();
    }

    export async function restoreVideoDefaults()
    {
        for (const it of videoOpts) {
            await deleteDefault(it.opt);
        }

        await registerVideoDefaults();
        await loadVideoSettings();
    }

    async function deleteDefault(opt: Opt)
    {
        try {
            // Try to add new database entry
            const id = await db.opts.delete(opt);
        } catch (error) {
            console.log("Failed to remove entry", opt);
        }
    }

    //
    // Loading settings
    //

    export async function loadSettings()
    {
        await loadGeneralSettings();
        await loadMachineSettings();
        await loadCompatibilitySettings();
        await loadAudioSettings();
        await loadVideoSettings();
    }

    export async function loadGeneralSettings()
    {
        for (const it of generalOpts) {
            await loadSetting(it.opt);
        }
    }

    export async function loadMachineSettings()
    {
        for (const it of machineOpts) {
            await loadSetting(it.opt);
        }
    }

    export async function loadCompatibilitySettings()
    {
        for (const it of compatibilityOpts) {
            await loadSetting(it.opt);
        }
    }

    export async function loadAudioSettings()
    {
        for (const it of audioOpts) {
            await loadSetting(it.opt);
        }
    }

    export async function loadVideoSettings()
    {
        for (const it of videoOpts) {
            await loadSetting(it.opt);
        }
    }

    async function loadSetting(opt: Opt)
    {
        try {
            // Read value from database
            const id = await db.opts.get(opt);

            // Apply setting
            set(opt, id.value);

        } catch (error) {
            // The entry is likely there already
        }
    }

    //
    // Saving settings
    //

    export async function saveSettings()
    {
        await saveGeneralSettings();
        await saveMachineSettings();
        await saveCompatibilitySettings();
        await saveAudioSettings();
        await saveVideoSettings();
    }

    export async function saveGeneralSettings()
    {
        for (const it of generalOpts) {
            await saveSetting(it.opt);
        }
    }

    export async function saveMachineSettings()
    {
        for (const it of machineOpts) {
            await saveSetting(it.opt);
        }
    }

    export async function saveCompatibilitySettings()
    {
        for (const it of compatibilityOpts) {
            await saveSetting(it.opt);
        }
    }

    export async function saveAudioSettings()
    {
        for (const it of audioOpts) {
            await saveSetting(it.opt);
        }
    }

    export async function saveVideoSettings()
    {
        for (const it of videoOpts) {
            await saveSetting(it.opt);
        }
    }

    async function saveSetting(opt: Opt)
    {
        const val = get(opt);

        try {
            // Write value into database
            const id = await db.opts.put({key: opt, value: val});

        } catch (error) {
            // The entry is likely there already
        }
    }

    //
    // Querying a config item
    //

    export function get(option: Opt): string
    {
        switch (option) {

            //
            // General settings
            //

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
            case Opt.WARP_MODE:
                return $amiga.getConfig($proxy.OPT_WARP_MODE).toString();
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
                return $amiga.getDriveConfig($proxy.OPT_HDC_CONNECT, 0).toString();
            case Opt.HD1:
                return $amiga.getDriveConfig($proxy.OPT_HDC_CONNECT, 1).toString();
            case Opt.HD2:
                return $amiga.getDriveConfig($proxy.OPT_HDC_CONNECT, 2).toString();
            case Opt.HD3:
                return $amiga.getDriveConfig($proxy.OPT_HDC_CONNECT, 3).toString();

                //
                // Compatibility settings
                //

            case Opt.BLITTER_ACCURACY:
                return $amiga.getConfig($proxy.OPT_BLITTER_ACCURACY).toString();
            case Opt.TODBUG:
                return $amiga.getConfig($proxy.OPT_TODBUG).toString();
            case Opt.PTR_DROPS:
                return $amiga.getConfig($proxy.OPT_PTR_DROPS).toString();
            case Opt.ECLOCK_SYNCING:
                return $amiga.getConfig($proxy.OPT_ECLOCK_SYNCING).toString();
            case Opt.DRIVE_SPEED:
                return $amiga.getConfig($proxy.OPT_DRIVE_SPEED).toString();
            case Opt.DRIVE_MECHANICS:
                return $amiga.getConfig($proxy.OPT_DRIVE_MECHANICS).toString();
            case Opt.OPT_LOCK_DSKSYNC:
                return $amiga.getConfig($proxy.OPT_LOCK_DSKSYNC).toString();
            case Opt.OPT_AUTO_DSKSYNC:
                return $amiga.getConfig($proxy.OPT_AUTO_DSKSYNC).toString();
            case Opt.CLX_SPR_SPR:
                return $amiga.getConfig($proxy.OPT_CLX_SPR_SPR).toString();
            case Opt.CLX_SPR_PLF:
                return $amiga.getConfig($proxy.OPT_CLX_SPR_PLF).toString();
            case Opt.CLX_PLF_PLF:
                return $amiga.getConfig($proxy.OPT_CLX_PLF_PLF).toString();
            case Opt.ACCURATE_KEYBOARD:
                return $amiga.getConfig($proxy.OPT_ACCURATE_KEYBOARD).toString();

            //
            // Audio settings
            //

            case Opt.SAMPLING_METHOD:
                return $amiga.getConfig($proxy.OPT_SAMPLING_METHOD).toString();
            case Opt.FILTER_TYPE:
                return $amiga.getConfig($proxy.OPT_FILTER_TYPE).toString();
            case Opt.AUDVOL0:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 0).toString();
            case Opt.AUDVOL1:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 1).toString();
            case Opt.AUDVOL2:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 2).toString();
            case Opt.AUDVOL3:
                return $amiga.getDriveConfig($proxy.OPT_AUDVOL, 3).toString();
            case Opt.AUDVOLL:
                return $amiga.getConfig($proxy.OPT_AUDVOLL).toString();
            case Opt.AUDVOLR:
                return $amiga.getConfig($proxy.OPT_AUDVOLR).toString();
            case Opt.STEP_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_STEP_VOLUME, 0).toString();
            case Opt.POLL_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_POLL_VOLUME, 0).toString();
            case Opt.INSERT_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_INSERT_VOLUME, 0).toString();
            case Opt.EJECT_VOLUME:
                return $amiga.getDriveConfig($proxy.OPT_EJECT_VOLUME, 0).toString();

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

    export function getNum(opt: Opt): number
    {
        return Number(get(opt));
        /*
        let result = get(option);
        return result === 'true' ? 1 : result === 'false' ? 0 : Number(result);
        */
    }

    export function getBool(opt: Opt): boolean
    {
        return getNum(opt) != 0;
    }

    //
    // Setting a config item
    //

    export function set(option: Opt, val: string)
    {
        switch (option) {

            //
            // General settings
            //

            case Opt.THEME:
                setTheme(Number(val));
                break;
            case Opt.CANVAS_BORDER:
                canvasBorder = Number(val);
                break;
            case Opt.SHAKING:
                shaking = Number(val);
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
            case Opt.WARP_MODE:
                $amiga.configure($proxy.OPT_WARP_MODE, Number(val));
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
                if (val == 1) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 1, 1);
                if (val == 1) $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 2, 1);
                $amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, 3, val);
                break;
            case Opt.HD0:
                $amiga.configureDrive($proxy.OPT_HDC_CONNECT, 0, val);
                break;
            case Opt.HD1:
                $amiga.configureDrive($proxy.OPT_HDC_CONNECT, 1, val);
                break;
            case Opt.HD2:
                $amiga.configureDrive($proxy.OPT_HDC_CONNECT, 2, val);
                break;
            case Opt.HD3:
                $amiga.configureDrive($proxy.OPT_HDC_CONNECT, 3, val);
                break;

            //
            // Compatibility Settings
            //

            case Opt.BLITTER_ACCURACY:
                $amiga.configure($proxy.OPT_BLITTER_ACCURACY, Number(val));
                break;

            case Opt.TODBUG:
                $amiga.configure($proxy.OPT_TODBUG, Number(val));
                break;

            case Opt.PTR_DROPS:
                $amiga.configure($proxy.OPT_PTR_DROPS, Number(val));
                break;

            case Opt.ECLOCK_SYNCING:
                $amiga.configure($proxy.OPT_ECLOCK_SYNCING, Number(val));
                break;

            case Opt.DRIVE_SPEED:
                $amiga.configure($proxy.OPT_DRIVE_SPEED, Number(val));
                break;

            case Opt.DRIVE_MECHANICS:
                $amiga.configureDrive($proxy.OPT_DRIVE_MECHANICS, 0, Number(val));
                $amiga.configureDrive($proxy.OPT_DRIVE_MECHANICS, 1, Number(val));
                $amiga.configureDrive($proxy.OPT_DRIVE_MECHANICS, 2, Number(val));
                $amiga.configureDrive($proxy.OPT_DRIVE_MECHANICS, 3, Number(val));
                break;

            case Opt.OPT_LOCK_DSKSYNC:
                $amiga.configure($proxy.OPT_LOCK_DSKSYNC, Number(val));
                break;

            case Opt.OPT_AUTO_DSKSYNC:
                $amiga.configure($proxy.OPT_AUTO_DSKSYNC, Number(val));
                break;

            case Opt.CLX_SPR_SPR:
                $amiga.configure($proxy.OPT_CLX_SPR_SPR, Number(val));
                break;

            case Opt.CLX_SPR_PLF:
                $amiga.configure($proxy.OPT_CLX_SPR_PLF, Number(val));
                break;

            case Opt.CLX_PLF_PLF:
                $amiga.configure($proxy.OPT_CLX_PLF_PLF, Number(val));
                break;

            case Opt.ACCURATE_KEYBOARD:
                $amiga.configure($proxy.OPT_ACCURATE_KEYBOARD, Number(val));
                break;

            //
            // Audio settings
            //

            case Opt.SAMPLING_METHOD:
                $amiga.configure($proxy.OPT_SAMPLING_METHOD, Number(val));
                break;
            case Opt.FILTER_TYPE:
                $amiga.configure($proxy.OPT_FILTER_TYPE, Number(val));
                break;
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
                flickerWeight = Number(val);
                break;
            default:
                console.warn("set: Invalid option: ", option);
            // TODO: Throw exception
        }

        // Force reactive components to update
        $config = $config;
    }

    export function setNum(option: Opt, val: number)
    {
        set(option, val.toString());
    }

    export function setBool(option: Opt, val: boolean)
    {
        set(option, val ? 'true' : 'false');
    }

    //
    // Auxiliary functions
    //

    function setTheme(val: Theme)
    {
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
            default:
                console.warn("Invalid theme");
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