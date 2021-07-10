/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int startwithgaps	     = 1;	 /* 1 means gaps are used by default */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "Noto Sans:size=11", "FiraCode Nerd Font:11", "FontAwesome:size=9", "monospace:size=10" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char* const nord[]     = { "#2e3440", "#3b4252", "#434c5e", "#4c566a",
                                        "#d8dee9", "#e5e9f0", "#eceff4",
                                        "#8fbcbb", "#88c0d0", "#81a1c1", "#5e81ac",
                                        "#bf616a", "#d08770", "#ebcb8b", "#a3be8c", "#b48ead" };
static const char *colors[][3]      = {
	/*                  fg         bg         border   */
	[SchemeNorm]    = { nord[4], nord[0], nord[0] },
	[SchemeSel]     = { nord[0], nord[9],  nord[9]  },
        [SchemeUrg]     = { nord[0], nord[11],  nord[11]  },
	[SchemeStatus]  = { nord[4], nord[0],  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel] = { nord[0], nord[9],  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
        [SchemeTagsNorm]= { nord[4], nord[0],  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
        [SchemeInfoSel] = { nord[0], nord[9],  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
        [SchemeInfoNorm]= { nord[4], nord[0],  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
        //"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
        "systemctl", "--user", "import-environment", "DISPLAY", NULL,
        "/usr/libexec/polkitd", "--no-debug", NULL,
        "sh", "-c", "~/.fehbg", NULL,
        //"libinput-gestures", "-c", "/home/jash_maester/.config/libinput-gestures.conf", NULL, // Replaced with Touchegg
        "touchegg", "--quiet", NULL,
        "numlockx", "on", NULL,
        "/usr/bin/dunst", NULL,
        //"clipit", NULL, // Replace with clipmenu (Super + C)
        "clipmenud", NULL,
	//"gnome-terminal", NULL,
	"st", NULL,
        //"optimus-manager-qt", NULL,
        //"nm-applet", NULL,
        "dwmblocks", NULL,
        "picom", "-b", "--experimental-backend", NULL,
        "discord", NULL,
        "/usr/bin/kdeconnect-indicator", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/*
static const Rule rules[] = {*/
	/* class            instance      title       tags mask     isfloating   opacity      monitor */
/*	{ "Gimp",           NULL,         NULL,       0,            1,           1.0,             -1 },
	{ "firefox",        "Navigator",  NULL,       0,            0,           1.0,             -1 },
	{ "firefox",        "Devtools",   NULL,       0,            1,           1.0,             -1 },
	{ "firefox",        "Places",     "Library",  0,            1,           1.0,             -1 },
	{ "firefox",        "Toolkit",     "Picture-in-Picture",  0,            1,           1.0,             -1 },
	{ "firefox",        "Firefox",     "Quit and close tabs?",  0,            1,           1.0,             -1 },
	{ "Gnome-terminal", NULL,         NULL,       0,            0,           defaultopacity,  -1 },
	{ "Gnome-terminal", NULL,         "cmus v2.9.1", 1 << 8,    1,           defaultopacity,  -1 },
        { "Pavucontrol",    "pavucontrol",NULL,       0,            1,           defaultopacity,  -1 },
        { "mpv",            NULL,         NULL,       0,            1,           defaultopacity,  -1 },
    { "Gnome-calculator", "gnome-calculator", "Calculator",   0,    1,           defaultopacity,  -1 },
};
*/
static const Rule rules[] = {
	/* class            instance      title       tags mask     isfloating   monitor */
	{ "Gimp",           NULL,         NULL,       0,            1,           -1 },
	{ "firefox",        "Navigator",  NULL,       0,            0,           -1 },
	{ "firefox",        "Devtools",   NULL,       0,            1,           -1 },
	{ "firefox",        "Places",     "Library",  0,            1,           -1 },
	{ "firefox",        "Firefox",    "Quit and close tabs?",   0, 1,        -1 },
	{ "jetbrains-toolbox",  NULL,     NULL,       0,            1,           -1 },
	{ "Gnome-terminal", NULL,         NULL,       0,            0,           -1 },
	{ "Gnome-terminal", NULL,         "cmus v2.9.1", 1 << 8,    1,           -1 },
        { "Pavucontrol",    "pavucontrol",NULL,       0,            1,           -1 },
        { "mpv",            NULL,         NULL,       0,            1,           -1 },
    { "Gnome-calculator", "gnome-calculator", "Calculator",   0,    1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "horizgrid.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
        { "###",      horizgrid },
        { NULL,       NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_i", "-m", dmenumon, "-h", "23", NULL };
static const char *roficmd[] = { "rofi_launcher.sh", NULL };
static const char *sttermcmd[]  = { "st", NULL };
static const char *stmusiccmd[]  = { "st", "-e", "cmus", NULL };
static const char *updateBlockscmd[] = {"pkill", "-RTMIN+10", "dwmblocks", NULL};
static const char *browsercmd[]  = { "firefox", NULL };
static const char *gnometermcmd[]  = { "gnome-terminal", NULL };

//static const char *gnomemusiccmd[]  = { "gnome-terminal", "-e", "cmus", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key                         function            argument */
	{ MODKEY,                       XK_d,                       spawn,              {.v = dmenucmd} },                  // Spawn Dmenu
	{ MODKEY|ShiftMask,             XK_d,                       spawn,              {.v = roficmd} },                   // Spawn Rofi
	{ MODKEY,                       XK_Return,                  spawn,              {.v = sttermcmd } },                // Spawn Terminal
	{ ControlMask|Mod1Mask,         XK_t,                       spawn,              {.v = gnometermcmd } },             // Spawn Terminal
	{ MODKEY,                       XK_F3,                      spawn,              {.v = stmusiccmd } },               // Spawn Cmus
	{ MODKEY,                       XK_F1,                      spawn,              {.v = browsercmd } },               // Spawn Browser ( Default Firefox)
	{ MODKEY,                       XK_a,                       spawn,              SHCMD("skippy-xd") },               // Spawn Skippy-xd (Overview)
	{ MODKEY,                       XK_c,                       spawn,              SHCMD("clipmenu") },                // Spawn Clipmenu (dmenu)
        { MODKEY|ControlMask,           XK_m,                       spawn,              SHCMD("pavucontrol") },
        { 0,                            XF86XK_Calculator,          spawn,              SHCMD("gnome-calculator") },
        { 0,                            XF86XK_Launch1,             spawn,              SHCMD("nautilus") },
        { 0,                            XF86XK_MonBrightnessUp,     spawn,              SHCMD("light -A 5") },
        { 0,                            XF86XK_MonBrightnessDown,   spawn,              SHCMD("light -U 5") },
        { 0,                            XF86XK_KbdBrightnessUp,     spawn,              SHCMD("bash ~/.config/i3/scripts/keyboard_light.sh increase") },
        { 0,                            XF86XK_KbdBrightnessDown,   spawn,              SHCMD("bash ~/.config/i3/scripts/keyboard_light.sh decrease") },
        { 0,                            XK_Print,                   spawn,              SHCMD("flameshot screen -p ~/Pictures/screenshots") },
        { ShiftMask,                    XK_Print,                   spawn,              SHCMD("flameshot gui -p ~/Pictures/screenshots") },
        { 0,                            XF86XK_AudioRaiseVolume,    spawn,              SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; pkill -RTMIN+10 dwmblocks") },
        { 0,                            XF86XK_AudioLowerVolume,    spawn,              SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; pkill -RTMIN+10 dwmblocks") },
        { 0,                            XF86XK_AudioMute,           spawn,              SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; pkill -RTMIN+10 dwmblocks") },
        { 0,                            XF86XK_AudioPlay,           spawn,              SHCMD("playerctl play-pause") },
        { 0,                            XF86XK_AudioStop,           spawn,              SHCMD("playerctl play") },
        { 0,                            XF86XK_AudioNext,           spawn,              SHCMD("playerctl next") },
        { 0,                            XF86XK_AudioPrev,           spawn,              SHCMD("playerctl previous") },
        { MODKEY|ControlMask,           XK_l,                       spawn,              SHCMD("slock") },
	{ MODKEY,                       XK_b,                       togglebar,          {0} },                              // Toggle DWM Bar
	{ MODKEY|ShiftMask,             XK_j,                       rotatestack,        {.i = +1 } },                       // Rotate the Current Stack ++
	{ MODKEY|ShiftMask,             XK_k,                       rotatestack,        {.i = -1 } },                       // Rotate the Current Stack --
	{ MODKEY|ControlMask,           XK_j,                       pushdown,           {0} },                              // Push Clients/Windows Down the stack
	{ MODKEY|ControlMask,           XK_k,                       pushup,             {0} },                              // Push Clients/Windows Up the stack
	{ MODKEY,                       XK_j,                       focusstack,         {.i = +1 } },                       // Change focus to windows in the current stack
	{ MODKEY,                       XK_k,                       focusstack,         {.i = -1 } },                       // Change focus to windows in the current stack
	{ MODKEY,                       XK_h,                       setmfact,           {.f = -0.05} },                     // Change the horizontal ratio of tiled windows
	{ MODKEY,                       XK_l,                       setmfact,           {.f = +0.05} },                     // Change the horizontal ratio of tiled windows
	{ MODKEY,                       XK_i,                       incnmaster,         {.i = +1 } },                       // Re-arrange Tiled windows in the stack
	{ MODKEY,                       XK_u,                       incnmaster,         {.i = -1 } },                       // Re-arrange Tiled windows in the stack
        { MODKEY|ShiftMask,             XK_h,                       setcfact,           {.f = +0.25} },                     // Change the vertical ratio of tiled windows
        { MODKEY|ShiftMask,             XK_l,                       setcfact,           {.f = -0.25} },                     // Change the vertical ratio of tiled windows
        { MODKEY|ShiftMask,             XK_o,                       setcfact,           {.f =  0.00} },                     // Reset to default Vertical Ratio
	{ MODKEY|ShiftMask,             XK_Return,                  zoom,               {0} },                              // Puts the selected window to Master
	{ MODKEY,                       XK_Tab,                     view,               {0} },
	{ Mod1Mask,                     XK_F4,                      killclient,         {0} },                              // Kill Client/Window
	{ MODKEY,                       XK_Escape,                  killclient,         {0} },                              // Kill Client/Window
	{ MODKEY,                       XK_t,                       setlayout,          {.v = &layouts[0]} },               // Set Default Tiling Layout
        { MODKEY|ControlMask,           XK_KP_Subtract,             cyclelayout,        {.i = -1 } },                       // Cycle Between Layouts --
        { MODKEY|ControlMask,           XK_KP_Add,                  cyclelayout,        {.i = +1 } },                       // Cycle Between Layouts ++
	{ MODKEY,                       XK_space,                   togglefloating,     {0} },                              // Toggle Floating Window
        { MODKEY|ShiftMask,             XK_f,                       togglefullscr,      {0} },                              // Toggle Fullscreen
        { MODKEY|ShiftMask,             XK_space,                   togglealwaysontop,  {0} },                              // Toggle Always on-top floating
//	{ MODKEY,                       XK_0,                       view,               {.ui = ~0 } },
//	{ MODKEY|ShiftMask,             XK_0,                       tag,                {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,           {.i = -1 } },                       // Focus change monitors
	{ MODKEY,                       XK_period,                  focusmon,           {.i = +1 } },                       // Focus change monitors
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,             {.i = -1 } },                       // Move windows to different monitors
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,             {.i = +1 } },                       // Move windows to different monitors
        { MODKEY,                       XK_minus,                   setgaps,            {.i = -5 } },                       // Set Gaps --
        { MODKEY,                       XK_equal,                   setgaps,            {.i = +5 } },                       // Set Gaps ++
        { MODKEY|ShiftMask,             XK_minus,                   setgaps,            {.i = GAP_RESET } },                // Reset Gaps
        { MODKEY|ShiftMask,             XK_equal,                   setgaps,            {.i = GAP_TOGGLE } },               // Toggle Gaps
//	{ MODKEY|ShiftMask,		XK_KP_Add,                  changeopacity,      {.f = +0.1}},                       // Change Opacity ++
//	{ MODKEY|ShiftMask,		XK_KP_Subtract,             changeopacity,      {.f = -0.1}},                       // Change Opacity --
	TAGKEYS(                        XK_1,                                           0)
	TAGKEYS(                        XK_2,                                           1)
	TAGKEYS(                        XK_3,                                           2)
	TAGKEYS(                        XK_4,                                           3)
	TAGKEYS(                        XK_5,                                           4)
	TAGKEYS(                        XK_6,                                           5)
	TAGKEYS(                        XK_7,                                           6)
	TAGKEYS(                        XK_8,                                           7)
	TAGKEYS(                        XK_9,                                           8)
        { MODKEY,                       XK_0,                       spawn,              {0} },                              // Restart DWM Magically
        { MODKEY|ShiftMask,             XK_r,                       self_restart,       {0} },                              // Restart DWM Magically
	{ MODKEY|ShiftMask,             XK_c,                       quit,               {0} },                              // Kill DWM and logout
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button1,        spawn,          {.v = updateBlockscmd } },
        { ClkStatusText,        0,              Button2,        spawn,          {.v = sttermcmd } },
        { ClkStatusText,        0,              Button3,        spawn,          {.v = gnometermcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
