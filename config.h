/* See LICENSE file for copyright and license details. */

/* -- Constants -- */
/* commands */
#define TERMINAL 	    "st"
#define BROWSER 	    "qutebrowser"
#define BACKGROUND 	    "bg"
#define MUSIC 		    "ncspot"
#define EMOJI_PICKER        "emojipick"
#define CALCULATOR 	    "bc"
#define LAUNCHER            "dmenu_run"
#define LOCKER              "slock"
/* scratchpads */
#define SPTERM 		    "spterm"
#define SPCALC 		    "spcalc"
#define SPMUSIC 	    "spmusic"
#define XEVTITLE 	    "Event Tester"
/* X window classes */
#define TERMCLASS           "St"
#define FMCLASS             "Ranger"
/* key aliases */
#define MODKEY              Mod4Mask /* SUPER */
/* fonts */
#define FONT                "monospace:pixelsize=12"
#define TERM_FONT           "monospace:pixelsize=12"
#define ICON_FONT           "Twemoji:pixelsize=12:antialias=true:autohint=true"

/* -- Appearance -- */
static unsigned int borderpx                = 3;   /* border pixel of windows */
static unsigned int snap                    = 32;  /* snap pixel */
static unsigned int gappih                  = 20;  /* horiz inner gap between windows */
static unsigned int gappiv                  = 10;  /* vert inner gap between windows */
static unsigned int gappoh                  = 10;  /* horiz outer gap between windows and screen edge */
static unsigned int gappov                  = 30;  /* vert outer gap between windows and screen edge */
static int smartgaps                        = 0;   /* 1 means no outer gap when there is only one window */
static int showbar                          = 1;   /* 0 means no bar */
static int topbar                           = 1;   /* 0 means bottom bar */
static const unsigned int systraypinning    = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft     = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing    = 2;   /* systray spacing */
static const int systraypinningfailfirst    = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray                = 1;   /* 0 means no systray */
static const char *fonts[]                        = { FONT, ICON_FONT };
static const char dmenufont[]               = FONT;
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#504945";
static const char col_gray3[]       = "#bdae93";
static const char col_gray4[]       = "#ebdbb2";
static const char col_cyan[]        = "#cc241d";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2  },
	[SchemeSel]  = { col_gray4, col_gray2,  col_gray1 },
};

/* -- Scratchpads -- */
typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n",     SPTERM,  "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n",     SPCALC,  "-f", TERM_FONT, "-g", "50x20", "-e", CALCULATOR, "-lq", NULL };
const char *spcmd3[] = {TERMINAL, "-n",     SPMUSIC, "-g", "120x34" "-e", MUSIC, NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    { SPTERM,      spcmd1},
    { SPCALC,      spcmd2},
    { SPMUSIC,     spcmd3},
};

/* -- Tagging -- */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* class      instance    title       tags mask     isfloating   monitor */
    { TERMCLASS,  NULL,       NULL,       0,            0,           -1 }, /* every terminal  */
    /* scratchpads rules */
    { TERMCLASS,  SPTERM,     NULL,       SPTAG(0),     1,           -1 }, /* st scratchpad   */
    { TERMCLASS,  SPCALC,     NULL,       SPTAG(1),     1,           -1 }, /* bc scratchpad   */
    { TERMCLASS,  SPMUSIC,    NULL,       SPTAG(2),     1,           -1 }, /* ncspot scratchpad */
    { FMCLASS,    NULL,       NULL,       0,            1,           -1 }, /* tui file manager  */
};

/* -- Layout(s) -- */
#define FORCE_VSPLIT 1                                          /* nrowgrid layout: force two clients to always split vertically    */
#include "vanitygaps.c"
static const float mfact            = 0.55;                     /* factor of master area size [0.05..0.95] */
static const int nmaster            = 1;                        /* number of clients in master area */
static const int resizehints        = 1;                        /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen     = 1;                        /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol                   arrange function */
	{ "[]=",                    tile                    },  /* first entry is default */
	{ "[M]",                    monocle                 },  /* All windows on top of eachother                                  */
	{ "[@]",                    spiral                  },  /* Fibonacci spiral                                                 */
	{ "[\\]",                   dwindle                 },  /* Decreasing in size right and leftward                            */
	{ "H[]",                    deck                    },  /* Master on left, slaves in monocle-like mode on right             */
	{ "TTT",                    bstack                  },  /* Master on top, slaves on bottom                                  */
	{ "===",                    bstackhoriz             },
	{ "HHH",                    grid                    },
	{ "###",                    nrowgrid                },
	{ "---",                    horizgrid               },
	{ ":::",                    gaplessgrid             },
	{ "|M|",                    centeredmaster          },  /* Master in middle, slaves on sides                                */
	{ ">M>",                    centeredfloatingmaster  },  /* Same but master floats                                           */
	{ "><>",                    NULL                    },  /* no layout function means floating behavior */
	{ NULL,                     NULL                    },
};

/* key definitions */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* -- Bindings -- */
#include <X11/XF86keysym.h> /* Provides XF86XK_* keys (multimedia keys)  */
#include "movestack.c" /* Provides movestack function (patch) */
#include "shiftview.c" /* Provides shiftview function (patch) */
static const Key keys[] = {
    /* modifier                     key             function            argument */

    /* Move the focus to the next/previous/master window in the stack*/
    { MODKEY,                       XK_j,           focusstack,         {.i = +1 } },
    { MODKEY,                       XK_k,           focusstack,         {.i = -1 } },

    /* Move the focused window to the next/previous stack position */
    { MODKEY|ShiftMask,             XK_j,           movestack,          {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,           movestack,          {.i = -1 } },

    /* Show only the windows with the selected tag */
    { MODKEY,                       XK_1,           view,               {.ui = 1 << 0} },
    { MODKEY,                       XK_2,           view,               {.ui = 1 << 1} },
    { MODKEY,                       XK_3,           view,               {.ui = 1 << 2} },
    { MODKEY,                       XK_4,           view,               {.ui = 1 << 3} },
    { MODKEY,                       XK_5,           view,               {.ui = 1 << 4} },
    { MODKEY,                       XK_6,           view,               {.ui = 1 << 5} },
    { MODKEY,                       XK_7,           view,               {.ui = 1 << 6} },
    { MODKEY,                       XK_8,           view,               {.ui = 1 << 7} },
    { MODKEY,                       XK_9,           view,               {.ui = 1 << 8} },
    { MODKEY,                       XK_0,           view,               {.ui = ~0    } },
    { MODKEY,                       XK_Tab,         view,               {0           } }, /* previously selected tag */

    /* Replaces the tag for the focused window */
    { MODKEY|ShiftMask,             XK_1,           tag,                {.ui = 1 << 0} },
    { MODKEY|ShiftMask,             XK_2,           tag,                {.ui = 1 << 1} },
    { MODKEY|ShiftMask,             XK_3,           tag,                {.ui = 1 << 2} },
    { MODKEY|ShiftMask,             XK_4,           tag,                {.ui = 1 << 3} },
    { MODKEY|ShiftMask,             XK_5,           tag,                {.ui = 1 << 4} },
    { MODKEY|ShiftMask,             XK_6,           tag,                {.ui = 1 << 5} },
    { MODKEY|ShiftMask,             XK_7,           tag,                {.ui = 1 << 6} },
    { MODKEY|ShiftMask,             XK_8,           tag,                {.ui = 1 << 7} },
    { MODKEY|ShiftMask,             XK_9,           tag,                {.ui = 1 << 8} },
    { MODKEY|ShiftMask,             XK_0,           tag,                {.ui = ~0    } },

    /* Show/hide windows with the selected tag */
    { MODKEY|ControlMask,           XK_1,           toggleview,         {.ui = 1 << 0} },
    { MODKEY|ControlMask,           XK_2,           toggleview,         {.ui = 1 << 1} },
    { MODKEY|ControlMask,           XK_3,           toggleview,         {.ui = 1 << 2} },
    { MODKEY|ControlMask,           XK_4,           toggleview,         {.ui = 1 << 3} },
    { MODKEY|ControlMask,           XK_5,           toggleview,         {.ui = 1 << 4} },
    { MODKEY|ControlMask,           XK_6,           toggleview,         {.ui = 1 << 5} },
    { MODKEY|ControlMask,           XK_7,           toggleview,         {.ui = 1 << 6} },
    { MODKEY|ControlMask,           XK_8,           toggleview,         {.ui = 1 << 7} },
    { MODKEY|ControlMask,           XK_9,           toggleview,         {.ui = 1 << 8} },

    /* Add/remove the selected tag to the focused window */
    { MODKEY|ControlMask|ShiftMask, XK_1,           toggletag,          {.ui = 1 << 0} },
    { MODKEY|ControlMask|ShiftMask, XK_2,           toggletag,          {.ui = 1 << 1} },
    { MODKEY|ControlMask|ShiftMask, XK_3,           toggletag,          {.ui = 1 << 2} },
    { MODKEY|ControlMask|ShiftMask, XK_4,           toggletag,          {.ui = 1 << 3} },
    { MODKEY|ControlMask|ShiftMask, XK_5,           toggletag,          {.ui = 1 << 4} },
    { MODKEY|ControlMask|ShiftMask, XK_6,           toggletag,          {.ui = 1 << 5} },
    { MODKEY|ControlMask|ShiftMask, XK_7,           toggletag,          {.ui = 1 << 6} },
    { MODKEY|ControlMask|ShiftMask, XK_8,           toggletag,          {.ui = 1 << 7} },
    { MODKEY|ControlMask|ShiftMask, XK_9,           toggletag,          {.ui = 1 << 8} },

    /* Show only the windows with the previous/next tag */
    { MODKEY|ShiftMask,             XK_h,           shiftview,          { .i = -1 } },
    { MODKEY|ShiftMask,             XK_l,           shiftview,          { .i = 1  } },

    /* Move the focused window to the top of the stack (MASTER) */
    { MODKEY,                       XK_Return,      zoom,               {0           } },

    /* Increase the number of masters by 1 */
    { MODKEY,                       XK_o,           incnmaster,         {.i = +1     } },

    /* Decrease the number of masters by 1 */
    { MODKEY|ShiftMask,             XK_o,           incnmaster,         {.i = -1     } },

    /* Kill the focused window */
    { MODKEY|ShiftMask,             XK_BackSpace,   killclient,         {0           } },

    /* Change the current layout */
    { MODKEY,                       XK_t,           setlayout,          {.v = &layouts[0]}  }, /* tile */
    { MODKEY|ShiftMask,             XK_u,           setlayout,          {.v = &layouts[1]}  }, /* monocle */
    { MODKEY,                       XK_y,           setlayout,          {.v = &layouts[2]}  }, /* spiral */
    { MODKEY|ShiftMask,             XK_y,           setlayout,          {.v = &layouts[3]}  }, /* dwindle */
    { MODKEY,                       XK_u,           setlayout,          {.v = &layouts[4]}  }, /* deck */
    { MODKEY|ShiftMask,             XK_t,           setlayout,          {.v = &layouts[5]}  }, /* bstack */
    { MODKEY,                       XK_i,           setlayout,          {.v = &layouts[11]} }, /* centeredmaster */
    { MODKEY|ShiftMask,             XK_i,           setlayout,          {.v = &layouts[12]} }, /* centeredfloatingmaster */
    { MODKEY|ShiftMask,             XK_f,           setlayout,          {.v = &layouts[13]} }, /* floating */

    /* Make the focused window visible across all the tags (aka STICKY) */
    { MODKEY,                       XK_s,           togglesticky,       {0} },

    /* Make the focused window show in fullscreen */
    { MODKEY,                       XK_f,           togglefullscr,      {0} },

    /* Increase/decrease master's size */
    { MODKEY,                       XK_h,           setmfact,           {.f = -0.05} },
    { MODKEY,                       XK_l,           setmfact,           {.f = +0.05} },

    /* Manage gaps */
    { MODKEY,                       XK_a,           togglegaps,         {0         } }, /* Enable/disable gaps */
    { MODKEY|ShiftMask,             XK_a,           defaultgaps,        {0         } }, /* Restore default size */
    { MODKEY,                       XK_z,           incrgaps,           {.i = +3   } }, /* Increase size */
    { MODKEY,                       XK_x,           incrgaps,           {.i = -3   } }, /* Decrease size */
    { MODKEY|ShiftMask,             XK_x,           togglesmartgaps,    {0         } }, /* Enable/disable smart gaps */

    /* Show/hide status bar */
    { MODKEY,                       XK_b,           togglebar,          {0         } },

    /* Handle multiple monitors */
    { MODKEY,                       XK_Left,        focusmon,           {.i = -1   } },
    { MODKEY|ShiftMask,             XK_Left,        tagmon,             {.i = -1   } },
    { MODKEY,                       XK_Right,       focusmon,           {.i = +1   } },
    { MODKEY|ShiftMask,             XK_Right,       tagmon,             {.i = +1   } },

    /* Move a window in/out of the stack (float) */
    { MODKEY|ShiftMask,             XK_space,       togglefloating,     {0         } },

    /* Toggle scratchpads */
    { MODKEY|ShiftMask,             XK_apostrophe,  togglescratch,      {.ui = 1   } }, /* bc */
    { MODKEY|ShiftMask,             XK_exclamdown,  togglescratch,      {.ui = 2   } }, /* spotify */
    { MODKEY|ShiftMask,             XK_dead_grave,  togglescratch,      {.ui = 0   } }, /* st */

    /* Launch commands */
    { MODKEY|ShiftMask,             XK_Return,                spawn,              {.v = termcmd} },
    { MODKEY,                       XK_w,                     spawn,              {.v = (const char*[]){ BROWSER, NULL } } },
    { MODKEY,                       XK_e,                     spawn,              {.v = (const char*[]){ EMOJI_PICKER, NULL } } },
    { MODKEY,                       XK_p,                     spawn,              {.v = (const char*[]){ LAUNCHER, NULL } } },
    { MODKEY|ShiftMask,             XK_comma,                 spawn,              {.v = (const char*[]){ LOCKER, NULL } } },
    { MODKEY|Mod1Mask,              XK_s,                     spawn,              SHCMD("scrot -s ~/Pictures/Screenshots/%b%d::%H%M%S.png")},
    { 0,                            XF86XK_MonBrightnessUp,   spawn,              SHCMD("brightnessctl -q set 5%+")},
    { 0,                            XF86XK_MonBrightnessDown, spawn,              SHCMD("brightnessctl -q set 5%-")},
    { 0,                            XF86XK_AudioRaiseVolume,  spawn,              SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%+")},
    { 0,                            XF86XK_AudioLowerVolume,  spawn,              SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%-")},
    { 0,                            XF86XK_AudioMute,         spawn,              SHCMD("wpctl set-mute @DEFAULT_SINK@ toggle")},

    /* End X session */
    { MODKEY|ShiftMask,             XK_q,           quit,               {0         } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

