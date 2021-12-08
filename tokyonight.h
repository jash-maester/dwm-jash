static const char* const tokyonight[]     = { "#2b2f40", "#d8dee9", "#e5e9f0", "#1a1b26", "#bf616a", "#000000"};

static const char *colors[][3]      = {
	/*                  fg         bg         border   */
	[SchemeNorm]    = { tokyonight[1], tokyonight[0],  	  tokyonight[0] 	 },
	[SchemeSel]     = { tokyonight[2], tokyonight[1],  	  tokyonight[3] 	 },
    [SchemeUrg]     = { tokyonight[0], tokyonight[4], 	  tokyonight[4]   },
	[SchemeStatus]  = { tokyonight[1], tokyonight[0],  	  tokyonight[5]  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel] = { tokyonight[2], tokyonight[3],  	  tokyonight[5]  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]= { tokyonight[1], tokyonight[0],  	  tokyonight[5]  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel] = { tokyonight[2], tokyonight[3],  	  tokyonight[5]  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]= { tokyonight[1], tokyonight[0],  	  tokyonight[5]  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
