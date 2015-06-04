$ ->
  $('td').on 'click', ->
    console.log $(@).data 'x'
    console.log $(@).data 'y'