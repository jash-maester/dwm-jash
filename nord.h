static const char* const nord[]     = { "#2e3440", "#d8dee9", "#81a1c1", "#bf616a", "#000000"};
static const char *colors[][3]      = {
	/*                  fg         bg         border   */
	[SchemeNorm]    = { nord[1], nord[0],  	  nord[0] 	 },
	[SchemeSel]     = { nord[0], nord[2],  	  nord[2] 	 },
    [SchemeUrg]     = { nord[0], nord[3], 	  nord[3]   },
	[SchemeStatus]  = { nord[1], nord[0],  	  nord[4]  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel] = { nord[0], nord[2],  	  nord[4]  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]= { nord[1], nord[0],  	  nord[4]  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel] = { nord[0], nord[2],  	  nord[4]  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]= { nord[1], nord[0],  	  nord[4]  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
