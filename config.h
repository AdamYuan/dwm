/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int gappx = 12;       /* gap pixel between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const char *const panel[] = { "xfce4-panel", "Xfce4-panel" }; /* name & cls of panel win */

static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */

static const int focusonwheel = 0;
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always };
static const int showtab = showtab_auto; /* Default tab bar show mode */
static const int toptab = False;         /* False means bottom tab bar */

static const char *fonts[] = {"Noto Sans:pixelsize=16:style=Bold:antialias=true"};
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = {"#aaaaaa", "#222B2E", "#222B2E"},
	[SchemeSel] = {"#000000", "#2EB398", "#2EB398"},
	[SchemeTitle] = {"#ffffff", "#222B2E", "#222B2E"},
};

/* autostart */
static const char *const autostart[] = {
	"feh", "--bg-scale", "/usr/share/backgrounds/xfce/default-adapta-lockscreen.jpg", NULL,
	"xfce4-screensaver", NULL,
	"xfsettingsd", "--sm-client-disable", NULL, 
	"start-pulseaudio-x11", NULL,
	"xfce4-power-manager", NULL,
	"/usr/lib/xfce4/notifyd/xfce4-notifyd", NULL,
	"compton", NULL,
	"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"sh", "-c", "GDK_BACKEND=x11 pamac-tray", NULL,
	"fcitx5", NULL,
	"xfce4-panel", "--disable-wm-check", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Steam",    NULL,       "Friends List", 0,            1,           -1 },
	{ panel[1],   NULL,       NULL,       (1 << 9) - 1, 0,           -1 },
};

/* layout(s) */
static const float mfact = 0.7;  /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;     /* number of clients in master area */
static const int nmaxmaster = 2;        /* maximum number of clients allowed in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{"[]=", tile}, /* first entry is default */
	//{"><>", NULL}, /* no layout function means floating behavior */
	{"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG) \
{MODKEY, KEY, view, {.ui = 1 << TAG}}, {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
{MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}}, \
{MODKEY | Mod1Mask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) \
{ \
	.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
}

/* commands */
#define TERM "xfce4-terminal"
#define TERMRUN TERM " -e "

static const char *rofiruncmd[] = {"rofi", "-show", "drun", "-modi", "drun", "-show-icons", "-font", "Noto Sans 16", "-icon-theme", "Papirus-Dark", "-run-shell-command", TERMRUN "{cmd}", NULL};
static const char *rofiquitcmd[] = {"rofi", "-show", "p", "-modi", "p:rofi-power-menu", "-font", "NotoSans Nerd Font Regular 16", "-width", "20", "-lines", "6", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	//{MODKEY, XK_b, togglebar, {0}},
	//{MODKEY, XK_w, tabmode, {-1}},
	{MODKEY, XK_j, focusstack, {.i = +1}},
	//{MODKEY, XK_Right, focusstack, {.i = +1}},
	{MODKEY, XK_k, focusstack, {.i = -1}},
	//{MODKEY, XK_Left, focusstack, {.i = -1}},
	{MODKEY, XK_h, setmfact, {.f = -0.05}},
	//{MODKEY, XK_Down, setmfact, {.f = -0.05}},
	{MODKEY, XK_l, setmfact, {.f = +0.05}},
	//{MODKEY, XK_Up, setmfact, {.f = +0.05}},
	{MODKEY, XK_o, zoom, {0}},
	{MODKEY, XK_equal, incnmaster, {.i = +1}},
	{MODKEY, XK_minus, incnmaster, {.i = -1}},

	{MODKEY, XK_Tab, view, {0}},
	{MODKEY, XK_x, killclient, {0}},
	{MODKEY, XK_d, setlayout, {0}},
	{MODKEY, XK_space, togglefloating, {0}},
	{MODKEY, XK_f, togglefullscr, {0}},
	{MODKEY, XK_0, view, {.ui = ~0}},
	{MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
	//{MODKEY, XK_comma, focusmon, {.i = -1}},
	//{MODKEY, XK_period, focusmon, {.i = +1}},
	//{MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
	//{MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
	TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)

	{MODKEY, XK_e, spawn, {.v = rofiruncmd}},
	{MODKEY | ShiftMask, XK_q, spawn, {.v = rofiquitcmd}},
	{MODKEY, XK_Return, spawn, {.v = (const char *[]){TERM, NULL}}},
	{MODKEY, XK_t, spawn, {.v = (const char *[]){"thunar", NULL}}},
	{MODKEY, XK_w, spawn, {.v = (const char *[]){"firefox", NULL}}},
	//{MODKEY, XK_m, spawn, {.v = (const char *[]){"thunderbird", NULL}}},
	{0, XK_Print, spawn, {.v = (const char *[]){"xfce4-screenshooter", NULL}}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ClkLtSymbol, 0, Button1, setlayout, {0}},
	{ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
	{ClkWinTitle, 0, Button2, zoom, {0}},
	//{ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
	{ClkClientWin, MODKEY, Button1, movemouse, {0}},
	{ClkClientWin, MODKEY, Button2, togglefloating, {0}},
	{ClkClientWin, MODKEY, Button3, resizemouse, {0}},
	{ClkTagBar, 0, Button1, view, {0}},
	{ClkTagBar, 0, Button3, toggleview, {0}},
	{ClkTagBar, MODKEY, Button1, tag, {0}},
	{ClkTagBar, MODKEY, Button3, toggletag, {0}},
	{ClkTabBar, 0, Button1, focuswin, {0}},
};
