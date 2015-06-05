read_with_status = ($url) ->
  $response = {}
  $.ajax
    type: 'GET'
    url: $url
    async: false
    complete: ($data) ->
      $response =
        text: $data.responseText
        status: $data.status
  $response

$human_count = 0

draw_state = ->
  # Organizmy
  $request = read_with_status '/organisms'
  $content = JSON.parse $request.text
  $human_color = read_with_status('/human-color').text
  $human_count = 0

  $('td').css 'background', '#fff'
  for $organism in $content
    $organism = JSON.parse $organism
    $('td[data-x="'+$organism[0]+'"][data-y="'+$organism[1]+'"]').css 'background', $organism[2]
    ++$human_color if $human_color == $organism[2]

  # Informacje
  $request = read_with_status '/log'
  $content = JSON.parse $request.text

  $('#info-panel').find('p').remove()
  for $info in $content
    $('#info-panel').append '<p>'+$info+'</p>'

$ ->
  draw_state()

  $('td').on 'click', ->
    console.log $(@).data 'x'
    console.log $(@).data 'y'

  $('button#next-round').on 'click', ->
    read_with_status 'next-round'
    draw_state()