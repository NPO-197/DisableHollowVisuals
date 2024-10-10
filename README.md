# DisableHollowVisuals
Simple mod that disables the visual effects of going hollow. You will still have all the mechanical effects of going hollow like lower max HP,
however the players physical appearance will remain as if you are in
human form, skin, eyes, hair, will remain unchanged.

This is a simple mod that takes the function that draws the player, and patches it
to read from an incorrect (empty) address when checking the players
hollow state. Thus the player is drawn as if they are in "hollow state
zero" (human form) regardless of the players *actual* hollow state.
