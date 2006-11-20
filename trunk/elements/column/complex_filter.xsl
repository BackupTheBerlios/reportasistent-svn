<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne en) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="column_name" label="Column name"/>
            <attribute name="value_type" label="Data type"/>
            <attribute name="primary_key_position" label="Primary key"/>
            <attribute name="min" label="Min" numeric_sort="true"/>
            <attribute name="max" label="Max" numeric_sort="true"/>
            <attribute name="avg" label="Avg" numeric_sort="true"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="column_name" label="Jméno sloupce"/>
            <attribute name="value_type" label="Datový typ"/>
            <attribute name="primary_key_position" label="Primární klíč"/>
            <attribute name="min" label="Min" numeric_sort="true"/>
            <attribute name="max" label="Max" numeric_sort="true"/>
            <attribute name="avg" label="Avg" numeric_sort="true"/>
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->
      </attributes>

      <values>
        <xsl:apply-templates select="column" mode="values"/>
      </values>

    </dialog_data>

  </xsl:template>


  
  
  


  <!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">


    <xsl:element name="value">
      <xsl:for-each select="@*">
        <xsl:attribute name="{name()}">
          <xsl:value-of select="."/>
        </xsl:attribute>
      </xsl:for-each>
    </xsl:element>
		
	</xsl:template>


</xsl:stylesheet>
