<?php
/**
 * @file
 * @codingStandardsIgnoreStart
 *
 * IDX Client.  A PHP wrapper around the IDX member.* APIs
 *
 * This client requires the curl module with SSL support enabled.
 * It has been tested in PHP 5.2 and PHP 5.3.  Other versions may work but are not
 * supported.
 *
 * @author Josh Mast <joshua.mast@nbcuni.com>
 * @author Chris Nelson <chris.z.nelson@nbcuni.com>
 *
 */

/**
 * A PHP wrapper around the IDX member.* APIs
 */
class IDXClient {
    private $apikey;
    private $brandid;
    private $api;
    private $curl;

    /**
     * Ensure we have the support we need and setup the object for future calls
     *
     * @param string $apikey. A valid api key / client id
     *
     * @param string $brandid.  The brand id to use for all write methods.
     * This is provided as a convenience but can be overridden for each method
     *
     * @param array $api. Information about the IDX api server including the
     * non-relative url (defaults to https:///idxapi.nbcuni.com/) and optionally
     * the proxy to use to connect.
     *
     *
     * @throws RuntimeException
     * @throws InvalidArgumentException
     */
    public function __construct($apikey, $brandid = NULL, $api = array('url' => 'https://stage.idxapi.nbcuni.com/'), $debug = FALSE) {
        //ensure curl exists
        if (function_exists('curl_version')) {
            $version = curl_version();
            if (!($version['features'] & CURL_VERSION_SSL)) {
                throw new RuntimeException('cURL SSL support is required for IDXClient to function.');
            }
        } else {
            throw new RuntimeException('cURL support is required for IDXClient to function.');
        }

        //ensure the endpoint is valid
        $parsed = parse_url($api['url']);
        if (!isset($parsed['scheme']) || !isset($parsed['host']) || !isset($parsed['path']) || (substr($api['url'], -1) != '/')) {
            throw new InvalidArgumentException($api['url'].' is not a valid non-relative url.');
        }

        //stash our variables for later use
        $this->apikey = $apikey;
        $this->brandid = $brandid;
        $this->endpoint = $api['url'];
        if (isset($api['proxy'])) $this->proxy = $api['proxy'];
        $this->debug = $debug;

        //setup our curl client
        $this->curl = curl_init();
        curl_setopt($this->curl, CURLOPT_VERBOSE, FALSE);
        curl_setopt($this->curl, CURLOPT_AUTOREFERER, FALSE);
        curl_setopt($this->curl, CURLOPT_BINARYTRANSFER, TRUE);
        curl_setopt($this->curl, CURLOPT_FAILONERROR, FALSE);
        curl_setopt($this->curl, CURLOPT_FILETIME, FALSE);
        curl_setopt($this->curl, CURLOPT_FOLLOWLOCATION, TRUE);
        curl_setopt($this->curl, CURLOPT_FORBID_REUSE, TRUE);
        curl_setopt($this->curl, CURLOPT_FRESH_CONNECT, TRUE);
        curl_setopt($this->curl, CURLOPT_RETURNTRANSFER, TRUE);
        curl_setopt($this->curl, CURLOPT_NETRC, FALSE);
        curl_setopt($this->curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_setopt($this->curl, CURLOPT_USERAGENT, "IDXClient.class.php");

        if (isset($this->proxy)) {
            curl_setopt($this->curl, CURLOPT_PROXY, $this->proxy);
        }

    }

    /**
     * Private method for generating a specific cURL request
     *
     * @param string $method The HTTP Method for this request, must be 'GET' or 'POST'
     *
     * @param string $target The path to request, will be appended to $this->endpoint
     * which can be set in the constructor.
     *
     * @param array data  Key/Value pairs to be added to the query string or POST body.
     *
     * @param array headers Key/Value pairs to be sent as headers: 'Content-Type' => 'text/plain'
     *
     * @param string|array brands.  If set, the brands to use for this request.  If not set
     * uses the brands specified in the constructor.  If that is not set and the method is POST
     * an exception will be thrown. If GET, all available brands will be used.
     *
     * @return string curl something
     *
     * @throws InvalidArgumentException
     * @throws UnexpectedValueException
     * @throws RuntimeException
     * @throws MemberNotFoundException
     * @throws MemberConflictException
     */
    private function request($method, $target, $data = NULL, $headers = NULL, $brands = NULL) {
        //make sure we can handle the method
        switch (strtoupper($method)) {
            case 'GET':
                $method = CURLOPT_HTTPGET;
                $method_name = "GET";
                break;
            case 'POST':
                $method = CURLOPT_POST;
                $method_name = "POST";
                break;
            default:
                throw new InvalidArgumentException('Only GET and POST are supported.');
        }

        //reformat our headers the way cURL wants them
        if (!$headers) {
            $headers = Array();
        } elseif (!is_array($headers)) {
            $headers = Array($headers);
        }
        $curl_headers = Array();
        foreach ($headers as $key => $value) {
            array_push($curl_headers, $key . ': '. $value);
        }

        //default to class level brands if not specified
        if (!$brands) {
            $brands = $this->brandid;
        }

        //if we are POST make sure we have a brand
        if (!$brands && $method == CURLOPT_POST) {
            throw new InvalidArgumentException('You must specify a single brand when calling a POST method.');
        }

        //if we aren't, convert to an array for easy mangling
        if (!is_array($brands)) {
            $brands = Array($brands);
        }

        //now let's build our querystring,
        //we don't use http_build_query() because for things like multiple brandids
        // it does it the php way (with braces) which is not standard at all
        $query_string = 'API_KEY=' . urlencode($this->apikey);
        foreach ($brands as $brand) {
            if (!$brand) {
                continue;
            }
            $query_string .= '&BRAND_ID=' . urlencode($brand);
        }

        //if we are GET, then we need to use data as part of the query string
        if ($method == CURLOPT_HTTPGET) {
            if (is_array($data)) {
                foreach ($data as $key => $value) {
                    $query_string .= '&' . urlencode($key) . '=' . urlencode($value);
                }
            } else {
                $query_string .= $data;
            }
        }

        //we should have our querystring now, so we can set our entire url
        curl_setopt($this->curl, CURLOPT_URL, $this->endpoint . $target . '?' . $query_string);

        //set the method
        curl_setopt($this->curl, $method, TRUE);

        //if we are post, use the data that way instead
        if ($method == CURLOPT_POST) {
            if (is_object($data) || is_array($data)) $data = http_build_query($data);
            curl_setopt($this->curl, CURLOPT_POSTFIELDS, $data);
        }

        //set any headers for get and post
        curl_setopt($this->curl, CURLOPT_HTTPHEADER, $curl_headers);

        if ($this->debug == TRUE) {
            $idxlog = fopen('/tmp/idx.log', 'a');
            $output_string = "--- " . strftime('%c', $_SERVER['REQUEST_TIME']) . " --- \r\n";
            $output_string .= "Request: " . $_SERVER['REQUEST_URL'] . "\r\n";
            $output_string .= "Script: " . $_SERVER['SCRIPT_NAME'] . "\r\n";
            $output_string .= "IDX Curl: " . $method_name . " " . $this->endpoint . $target . '?' . $query_string . "\r\n";
            $output_string .= "Data: " . json_encode($data) . "\r\n";
            fwrite($idxlog, $output_string);
        }

        //and rock it out \m/
        $result = curl_exec($this->curl);

        if (!$result && curl_error($this->curl)) { // something 204 or 302 blanks and I needed to change this, but I don't remember what.
            $error = curl_error($this->curl);
            $code = curl_errno($this->curl);
            error_log("Problem connecting to IDX HTTP API: (" . $code . ") " . $error);
            throw new RuntimeException("Problem connecting to IDX HTTP API: (" . $code . ") " . $error, 502);
        }

        $code = intval(curl_getinfo($this->curl, CURLINFO_HTTP_CODE));

        if ($this->debug == TRUE) {
            fwrite($idxlog, "response " . $code . ": " . $result . "\r\n");
            fwrite($idxlog, "curl_exec finished at " . strftime('%c') . "\r\n\r\n");
            fclose($idxlog);
        }

        //we should ALWAYS get JSON back, so first make sure that happened
        $object = json_decode($result, TRUE);
        if (!$object && $code != 204) {
            switch (json_last_error()) {
                case "JSON_ERROR_DEPTH":
                    $json_error = 'Maximum stack depth exceeded';
                    break;
                case "JSON_ERROR_STATE_MISMATCH":
                    $json_error = 'Underflow or the modes mismatch';
                    break;
                case "JSON_ERROR_CTRL_CHAR":
                    $json_error = 'Unexpected control character found';
                    break;
                case "JSON_ERROR_SYNTAX":
                    $json_error = 'Syntax error, malformed JSON';
                    break;
                case "JSON_ERROR_UTF8":
                    $json_error = 'Malformed UTF-8 characters, possibly incorrectly encoded';
                    break;
                default:
                    $json_error = 'Unknown error';
            }

            throw new UnexpectedValueException('Unable to parse response from IDX as JSON: ' . $json_error);
        }

        //were we missing key parameters?
        if ($code == 400) {
            debug(func_get_args(), 'args');
            throw new InvalidArgumentException('IDX: ' . $object['error'], $code);
        }

        //did we have security problems or did something go terribly wrong?
        if ($code == 401 || $code == 403 || $code >= 500) {
            throw new RuntimeException('IDX: ' . $object['error'], $code);
        }

        //ok request, but the member they asked us to operate on was not found.
        if ($code == 404) {
            throw new MemberNotFoundException($object['error'], $code);
        }

        //Member conflict
        if ($code == 409) {
            throw new MemberConflictException($object['error'], $code);
        }

        //everything ok?
        if ($code == 200 || $code = 302 || $code == 204) {
            return $object;
        }

        //hopefully we never end up here.
        throw new RuntimeException("Unexpected response code.", $code);
    }

    /**
     * Retrieve a member from the IDX system
     *
     * @param string $member_id A uuid, email address or username.
     *
     * @param string $view ('most-recent-user', 'most-recent-all', or 'best-guess')
     * How to filter the data on the user, defaults to most-recent-user (optional)
     *
     * @param string $brands The brands to retrieve data from, defaults to all (optional)
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found
     */
    public function memberGet($member_id, $view = NULL, $provider = 'idx', $brands = NULL) {
        $data = Array('id' => $member_id,'provider' => $provider);
        //if we have a view set it
        if (isset($view)) {
            $data['view'] = $view;
        }

        return $this->request('GET', 'member/get', $data, NULL, $brands);
    }

    /**
     * Put a member into the IDX system
     *
     * @param array $member An array (possibly of arrays) representing the member to save.
     * Field names should match what is returned from memberGet
     * To update a member ensure $member has the "_id" parameter set of the member you want to update.
     * To add a new member, do not specify an "_id".
     *
     * @param string $brand The brand affected by this operation, if not set, will use the brand specified
     * in the constructor if it was only one brand.
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found for updating
     * @throws MemberConflictException the member already exists in the database
     */
    public function memberPut($member, $brand = NULL) {
        if (is_array($member)) {
            $member = json_encode($member);
        }

        return $this->request('POST', 'member/put', $member, Array('Content-Type' => 'application/json'), $brand);
    }

    /**
     * Delete a member from the IDX system
     * This just flags a member as deleted, no data is actually removed.
     *
     * @param string $member_id the id of the member to remove.
     *
     * @param string $brand The brand affected by this operation, if not set, will use the brand specified
     * in the constructor if it was only one brand.
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found for deletion
     */
    public function memberDelete($member_id, $brand = NULL) {
        return $this->request('POST', 'member/delete', Array("id" => $member_id), NULL, $brand);
    }

    /**
     * Delete a member from the IDX system
     * This data is actually removed.
     *
     * @param string $member_id the id of the member to remove.
     *
     * @param string $brand The brand affected by this operation, if not set, will use the brand specified
     * in the constructor if it was only one brand.
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found for deletion
     */
    public function memberRemove($member_id, $brand = NULL) {
        return $this->request('POST', 'member/remove', Array("id" => $member_id), NULL, $brand);
    }


    /**
     * Authenticates a member in the IDX system
     *
     * @param string $member_id the id of the member to login.  Can be a UUID, email address or username
     *
     * @param string $password the password to authenticate with
     *
     * @param string $brand The brand affected by this operation, if not set, will use the brand specified
     * in the constructor if it was only one brand.
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found or their password was invalid
     */
    public function memberLogin($member_id, $password, $brand = NULL) {
        return $this->request('POST', 'member/login', Array("id"=> $member_id, "password" => $password), NULL, $brand);
    }

    public function socialLogin($timestamp, $uid, $signature, $apiKey, $brand = NULL) {
        return $this->request('POST', 'member/login', Array("id"=> $uid, "UIDSignature" => $signature, "signatureTimestamp"=>$timestamp, "gigya_api_key"=> $apiKey), NULL, $brand);
    }


    /**
     * Marks a member as logged out in the IDX system
     *
     * @param string $member_id the id of the member to logout.  Can be a UUID, email address or username
     *
     * @param string $brand The brand affected by this operation, if not set, will use the brand specified
     * in the constructor if it was only one brand.
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found
     */
    public function memberLogout($member_id, $gigya_api_key = NULL, $brand = NULL) {
        return $this->request('POST', 'member/logout', Array("id"=> $member_id, "gigya_api_key" => $gigya_api_key), NULL, $brand);
    }


    /**
     * Links a member to a social provider in IDX
     *
     * @param string $member_id the id of the member to link.
     *
     * @param string $provider the name of the provider to link with
     *
     * @param int $provider_id the uid for the member in this provider
     *
     * @param string $brand The brand affected by this operation, if not set, will use the brand specified
     * in the constructor if it was only one brand.
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found
     * @throws InvalidArgumentException the provider or provider id was not valid
     */
    public function memberLink($member_id, $provider, $provider_id, $apiKey, $brand = NULL) {
            return $this->request('POST', 'member/link', Array("id" => $member_id, "provider" => $provider, "provider_id" => $provider_id, "brand" => $brand, "gigya_api_key"=>$apiKey));
    }


    /**
     * Unlinks a member from a social provider in IDX
     *
     * @param string $member_id the id of the member to unlink.
     *
     * @param string $provider the name of the provider to unlink
     *
     * @param int $provider_id the uid for the member in this provider
     *
     * @param string $brand The brand affected by this operation, if not set, will use the brand specified
     * in the constructor if it was only one brand.
     *
     * @return array representation of the member
     *
     * @throws MemberNotFoundException the member requested cannot be found
     * @throws InvalidArgumentException the provider or provider id was not valid
     */
    public function memberUnlink($member_id, $provider, $provider_id, $brand = NULL) {
        return $this->request('POST', 'member/unlink', Array("id" => $member_id, "provider" => $provider, "provider_id" => $provider_id, "brand" => $brand), $brand);
    }


    /**
     * Search for members in the idx system
     *
     * @param array $query key/values to search for.  Can be any field returned in memberGet()
     *
     * @param string type 'and' or 'or'.  The type of search to perform.  Defaults to and
     *
     * @param string $view ('most-recent-user', 'most-recent-all', or 'best-guess')
     * How to filter the data on the user, defaults to most-recent-user (optional)
     *
     * @param string $per_page The number of items to return per page.  10-100
     *
     * @param in $index A pointer to retrieve additional pages of search results.
     * When retrieving more than one page of results you must supply the value of index returned
     * by your previous search query
     *
     * @param string $brands The brands to retreive data from, defaults to all (optional)
     *
     * @return array representation of the search results
     *
     */
    public function memberSearch($query, $type='and', $view=NULL, $per_page=NULL, $index=NULL, $brand = NULL) {
        //make sure the query is an array
        if (!is_array($query)) {
            $query = Array($query);
        }

        //pack our other variables into it, if they've been set
        $query['type'] = $type;

        if (isset($view)) {
            $query['view'] = $view;
        }

        if (isset($per_page)) {
            $query['per_page'] = $per_page;
        }

        if (isset($index)) {
            $query['index'] = $index;
        }

        return $this->request('GET', 'member/search', $query, NULL, $brand);
    }
}

//Simple custom names for Runtime exceptions to allow them to be easily caught.
class MemberNotFoundException extends RuntimeException {};

class MemberConflictException extends RuntimeException {};
