<?php


/**
 * @info Block Footer
 * @region footer
 * @visibility 1
 * @pages page/1|page/2
 * @status 1
 * @cache BLOCK_NO_CACHE
 * @weight 0
 */
function block_footer() {
       return array(
         'subject' => t('Block Footer'),
         'content' => 'Fooooter by Attestation Légale',
       );
}