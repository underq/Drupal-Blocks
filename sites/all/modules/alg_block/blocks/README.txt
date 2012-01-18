Declare a block or set of blocks.

Any module can declare a block (or blocks) to be displayed by implementing hook_block(), which also allows you to specify any custom configuration settings, and how to display the block.

In hook_block(), each block your module provides is given a unique identifier referred to as "delta" (the array key in the return value for the 'list' operation). Delta values only need to be unique within your module, and they are used in the following ways:

Passed into the other hook_block() operations as an argument to identify the block being configured or viewed.
Used to construct the default HTML ID of "block-MODULE-DELTA" applied to each block when it is rendered (which can then be used for CSS styling or JavaScript programming).
Used to define a theming template suggestion of block__MODULE__DELTA, for advanced theming possibilities.
The values of delta can be strings or numbers, but because of the uses above it is preferable to use descriptive strings whenever possible, and only use a numeric identifier if you have to (for instance if your module allows users to create several similar blocks that you identify within your module code with numeric IDs).

Parameters

$op What kind of information to retrieve about the block or blocks. Possible values:

'list': A list of all blocks defined by the module.
'configure': Configuration form for the block.
'save': Save the configuration options.
'view': Process the block when enabled in a region in order to view its contents.
$delta Which block to return (not applicable if $op is 'list'). See above for more information about delta values.

$edit If $op is 'save', the submitted form data from the configuration form.

Return value

If $op is 'list': An array of block descriptions. Each block description is an associative array, with the following key-value pairs:
'info': (required) The human-readable name of the block. This is used to identify the block on administration screens, and is not displayed to non-administrative users.
'cache': A bitmask of flags describing how the block should behave with respect to block caching. The following shortcut bitmasks are provided as constants in block.module:
BLOCK_CACHE_PER_ROLE (default): The block can change depending on the roles the user viewing the page belongs to.
BLOCK_CACHE_PER_USER: The block can change depending on the user viewing the page. This setting can be resource-consuming for sites with large number of users, and should only be used when BLOCK_CACHE_PER_ROLE is not sufficient.
BLOCK_CACHE_PER_PAGE: The block can change depending on the page being viewed.
BLOCK_CACHE_GLOBAL: The block is the same for every user on every page where it is visible.
BLOCK_NO_CACHE: The block should not get cached.
'weight': (optional) Initial value for the ordering weight of this block. Most modules do not provide an initial value, and any value provided can be modified by a user on the block configuration screen.
'status': (optional) Initial value for block enabled status. (1 = enabled, 0 = disabled). Most modules do not provide an initial value, and any value provided can be modified by a user on the block configuration screen.
'region': (optional) Initial value for theme region within which this block is set. Most modules do not provide an initial value, and any value provided can be modified by a user on the block configuration screen. Note: If you set a region that isn't available in the currently enabled theme, the block will be disabled.
'visibility': (optional) Initial value for the visibility flag, which tells how to interpret the 'pages' value. Possible values are:
0: Show on all pages except listed pages. 'pages' lists the paths where the block should not be shown.
1: Show only on listed pages. 'pages' lists the paths where the block should be shown.
2: Use custom PHP code to determine visibility. 'pages' gives the PHP code to use.
Most modules do not provide an initial value for 'visibility' or 'pages', and any value provided can be modified by a user on the block configuration screen.

'pages': (optional) See 'visibility' above.
If $op is 'configure': optionally return the configuration form.
If $op is 'save': return nothing; save the configuration values.
If $op is 'view': return an array which must define a 'subject' element (the localized block title) and a 'content' element (the block body) defining the block indexed by $delta. If the "content" element is empty, no block will be displayed even if "subject" is present.
For a detailed usage example, see block_example.module.