class AddNuspNameTypeAndGroup < ActiveRecord::Migration[5.1]
  def change
  	add_column :users, :name, :string
  	add_column :users, :nusp, :integer
  	add_column :users, :type, :boolean
  	add_reference :users, :group, foreign_key: true
  end
end
