module DeviseHelper

  #Função adaptada de: https://github.com/plataformatec/devise/wiki/Override-devise_error_messages!-for-views
  def devise_error_messages!
    return "" unless devise_error_messages?

    messages = resource.errors.full_messages.map { |msg| content_tag(:li, msg) }.join
    if resource.errors.count == 1
      sentence = "Ops! There was #{resource.errors.count} error:"
    else
      sentence = "Ops! There where #{resource.errors.count} errors:"
    end

    html = <<-HTML
    <div id="error_explanation" class="alert alert-danger">
      #{sentence}
      <ul>#{messages}</ul>
    </div>
    HTML

    html.html_safe
  end

  def devise_error_messages?
    !resource.errors.empty?
  end

end
