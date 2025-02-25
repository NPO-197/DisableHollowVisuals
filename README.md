# DisableHollowVisuals
Simple mod that disables the visual effects of going hollow. You will still have all the mechanical effects of going hollow like lower max HP,
however the players physical appearance will remain as if you are in
human form, skin, eyes, hair, will remain unchanged.

This is a simple mod that takes the function that draws the player, and patches it
to load a zero inplace of reading from the players hollow status. Thus the player is drawn as if they are in "hollow state
zero" (human form) regardless of the players *actual* hollow state.
